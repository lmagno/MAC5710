#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "heap.c"

#define BUFFER_SIZE 256
#define MAX 100

void get_count(const char *filename, int count[256]);
HeapNode* huffman(Heap *h);
void traverse(HeapNode *hn, char s[MAX], char codes[256][MAX]);
bool isleaf(HeapNode *hn);
void compress(char const *filename, char codes[256][MAX]);
void flush(char *output);

int main(int argc, char const *argv[]) {
    int i, count[256];
    char s[MAX], codes[256][MAX] = { "" };
    Heap *h;
    HeapNode *hn;

    get_count(argv[1], count);

    h = heap_create(256);
    for(i = 0; i < 256; i++) {
        if(count[i] == 0)
            continue;

        hn = heapnode_create(count[i], i);
        heap_push(h, hn);
    }


    hn = huffman(h);

    s[0] = '\0';
    traverse(hn, s, codes);

    // for(i = 0; i < 256; i++) {
    //     if(count[i] == 0)
    //         continue;
    //     printf("%04d\t%x\t%s\n", count[i], (uint8_t)i, codes[i]);
    // }
    compress(argv[1], codes);


    heapnode_free(hn);
    heap_free(h);
    return 0;
}

void compress(char const *filename, char codes[256][MAX]) {
    int i, r, n;
    char *s, output[128+1] = "";
    FILE *file;
    uint8_t buffer[BUFFER_SIZE];

    file = fopen(filename, "rb");
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    while(1) {
        r = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, file);
        if(ferror(file)) {
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", filename, r);
            exit(EXIT_FAILURE);
        }

        for(i = 0; i < r; i++) {
            s = codes[buffer[i]];
            printf("%x\t%s\n", (uint8_t)buffer[i], s);
            if(strlen(output) + strlen(s) > 128) {
                flush(output);
            }

            strcat(output, s);
        }

        if(feof(file)) break;
    }
    flush(output);
    
    n = strlen(output);
    for(i = 0; i < 8-n; i++) strcat(output, "0");
    for(i = 0; i < n;   i++) strcat(output, "1");
    for(i = 0; i < 8-n; i++) strcat(output, "0");
    flush(output);
    printf("%s\n", output);
    fclose(file);
}

void flush(char *output) {
    unsigned int offset;
    char s[9];

    offset = 0;
    while(1) {
        strncpy(s, output + offset, 8);
        s[9] = '\0';

        if(strlen(s) < 8) {
            strcpy(output, s);
            return;
        }

        printf("%s %x\n", s, (unsigned int)strtol(s, NULL, 2));
        offset += 8;
    }
}

void traverse(HeapNode *hn, char s[MAX], char codes[256][MAX]) {
    char sl[MAX], sr[MAX];

    if(!hn)
        return;

    if(isleaf(hn))
        strcpy(codes[hn->value], s);

    strcpy(sl, s);
    strcat(sl, "0");
    traverse(hn->left, sl, codes);

    strcpy(sr, s);
    strcat(sr, "1");
    traverse(hn->right, sr, codes);
}

bool isleaf(HeapNode *hn) {
    if(!hn)
        return false;
    else
        return !hn->left && !hn->right;
}

HeapNode* huffman(Heap *h) {
    HeapNode *hn, *hn1, *hn2;

    while(h->size > 1) {
        hn1 = heap_pop(h);
        hn2 = heap_pop(h);

        hn = heapnode_create(hn1->key + hn2->key, 0);
        hn->left  = hn1;
        hn->right = hn2;

        heap_push(h, hn);
    }

    return heap_pop(h);
}

void get_count(const char *filename, int count[256]) {
    int i, r;
    FILE *file;
    uint8_t buffer[BUFFER_SIZE];


    for(i = 0; i < 256; i++)
        count[i] = 0;

    file = fopen(filename, "rb");
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    while(1) {
        r = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, file);
        if(ferror(file)) {
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", filename, r);
            exit(EXIT_FAILURE);
        }

        for(i = 0; i < r; i++) {
            // printf("%x\n", buffer[i]);
            count[buffer[i]] += 1;
        }

        if(feof(file)) break;
    }
    fclose(file);
}

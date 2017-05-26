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

    for(i = 0; i < 256; i++) {
        if(count[i] == 0)
            continue;
        printf("%04d\t%x\t%s\n", count[i], (uint8_t)i, codes[i]);
    }
    fflush(stdout);
    printf("%ld %s\n", strtol("101", NULL, 2), "101");
    heapnode_free(hn);
    heap_free(h);
    return 0;
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

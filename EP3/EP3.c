#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "heap.c"

#define BUFFER_SIZE 256
#define MAX 1000
typedef HeapNode HuffmanTree;
const char *bits[16] = {
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

void get_count(const char *filename, int count[256]);
HuffmanTree* huffman(Heap *h);
int huffman_codes(HuffmanTree *hn, char s[MAX], char codes[256][MAX]);
bool isleaf(HuffmanTree *hn);
void compress(char const *finname, char const *foutname);
void flush(FILE *file, char *output);
void huffman_serialize(char *s, HuffmanTree *hn);


int main(int argc, char const *argv[]) {

    compress(argv[1], argv[2]);
    return 0;
}

void compress(char const *finname, char const *foutname) {
    int i, r, n, length, count[256];
    size_t size_in, size_out;
    char *s, *he, tmp[MAX] = "",
        buffer_out[BUFFER_SIZE+1] = "",
        codes[256][MAX] = { "" };
    FILE *fin, *fout;
    Heap *h;
    HeapNode *hn;
    HuffmanTree *ht;
    uint8_t buffer_in[BUFFER_SIZE];

    /* Get frequency count of bytes in file */
    get_count(finname, count);

    /* Put those frequencies in a heap */
    h = heap_create(256);
    for(i = 0; i < 256; i++) {
        if(count[i] == 0)
            continue;

        hn = heapnode_create(count[i], i);
        heap_push(h, hn);
    }

    /* Get Huffman tree */
    ht = huffman(h);

    /* Get the code of each byte and the length of the tree's serialization */
    length = huffman_codes(ht, tmp, codes); printf("length = %d\n", length);
    he = (char*)calloc(length+1, sizeof(char));

    /* Serialize the tree so we can write it to the output */
    huffman_serialize(he, ht); printf("Huffman = %s\n", he);


    fin = fopen(finname, "rb");
    if(!fin) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", finname);
        exit(EXIT_FAILURE);
    }

    fout = fopen(foutname, "wb");
    if(!fout) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", foutname);
        exit(EXIT_FAILURE);
    }

    /* Flush all complete bytes of the tree's serialization
    and keep the remaining bits in the output buffer */
    flush(fout, he);
    strcpy(buffer_out, he);
    free(he);

    /* Continuously read from input and write to output */
    while(1) {
        /* Read at most BUFFER_SIZE bytes from the input */
        r = fread(buffer_in, sizeof(uint8_t), BUFFER_SIZE, fin);
        if(ferror(fin)) {
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", finname, r);
            exit(EXIT_FAILURE);
        }

        /* If output buffer is full, flush complete bytes to the output */
        for(i = 0; i < r; i++) {
            s = codes[buffer_in[i]];
            // printf("%x\t%s\n", (uint8_t)buffer[i], s);
            if(strlen(buffer_out) + strlen(s) > BUFFER_SIZE+1) {
                flush(fout, buffer_out);
            }

            strcat(buffer_out, s);
        }

        if(feof(fin)) break;
    }
    /* Flush complete bytes to the output */
    flush(fout, buffer_out);

    /* Padding of last bits plus a byte with a mask */
    n = strlen(buffer_out);
    for(i = 0; i < 8-n; i++) strcat(buffer_out, "0");
    for(i = 0; i < n;   i++) strcat(buffer_out, "1");
    for(i = 0; i < 8-n; i++) strcat(buffer_out, "0");
    flush(fout, buffer_out);

    if(strlen(buffer_out) > 0) {
        fprintf(stderr, "ERROR: Wrong padding at end of file (%ld bits remaining).\n", strlen(buffer_out));
        exit(EXIT_FAILURE);
    }

    /* Print out statistics */
    size_in  = ftell(fin);
    size_out = ftell(fout);
    printf("Tamanho do arquivo original:   %ld\n", size_in);
    printf("Tamanho do arquivo comprimido: %ld\n", size_out);
    printf("Compressão: %.1f%%\n", 100*size_out/(double)size_in);


    heapnode_free(ht);
    heap_free(h);
    fclose(fin);
    fclose(fout);
}

void huffman_serialize(char *he, HuffmanTree *ht) {
    char s[20];

    if(!ht)
        return;

    if(isleaf(ht)) {
        sprintf(s, "1%s%s", bits[ht->value >> 4], bits[ht->value & 0x0F]);
        strcat(he, s);
    } else {
        strcat(he, "0");
        huffman_serialize(he, ht->left);
        huffman_serialize(he, ht->right);
    }
}

void flush(FILE *file, char *output) {
    unsigned int offset, size;
    uint8_t *buffer;
    char s[9];

    size = strlen(output)/8;
    buffer = (uint8_t*)malloc(size*sizeof(uint8_t));
    offset = 0;
    while(1) {
        strncpy(s, output + 8*offset, 8);
        s[8] = '\0';

        if(strlen(s) < 8) {
            fwrite(buffer, sizeof(uint8_t), offset, file);
            free(buffer);
            strcpy(output, s);
            return;
        }

        // printf("%s %x\n", s, (unsigned int)strtol(s, NULL, 2));
        buffer[offset] = (uint8_t)strtol(s, NULL, 2);
        // printf("%x\n", buffer[offset]);
        offset += 1;
    }

}

int huffman_codes(HuffmanTree *ht, char tmp[MAX], char codes[256][MAX]) {
    int length;
    char sl[MAX], sr[MAX];

    if(!ht)
        return 0;

    if(isleaf(ht)) {
        strcpy(codes[ht->value], tmp);
        printf("%x\t%s\n", ht->value, tmp);
        length = 9;
    } else {
        length = 1;

        strcpy(sl, tmp);
        strcat(sl, "0");
        length += huffman_codes(ht->left, sl, codes);

        strcpy(sr, tmp);
        strcat(sr, "1");
        length += huffman_codes(ht->right, sr, codes);
    }

    return length;
}

bool isleaf(HuffmanTree *ht) {
    if(!ht)
        return false;
    else
        return !ht->left && !ht->right;
}

HuffmanTree* huffman(Heap *h) {
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

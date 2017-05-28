#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "heap.c"
#include "buffer.c"
#include "queue.h"

#define MAX 1000
typedef HeapNode HuffmanTree;

void get_count(const char *filename, int count[256]);
HuffmanTree* huffman(Heap *h);
int huffman_codes(HuffmanTree *hn, char s[MAX], char codes[256][MAX]);
bool isleaf(HuffmanTree *hn);
void compress(char const *fname_in, char const *fname_out);
void decompress(char const *fname_in, char const *fname_out);
void flush(FILE *file, char *output);
void huffman_serialize(char *s, HuffmanTree *hn);
HuffmanTree* huffman_deserialize(Buffer *b);

int main(int argc, char const *argv[]) {
    if(argc != 4) {
        fprintf(stderr, "Wrong number of arguments given, check README file for instructions.\n");
        exit(EXIT_FAILURE);
    }

    switch(argv[1][0]) {
        case 'c':
            printf("Compressing '%s' to '%s'...\n\n", argv[2], argv[3]);
            compress(argv[2], argv[3]);
            break;
        case 'd':
            printf("Decompressing '%s' to '%s'...\n\n", argv[2], argv[3]);
            decompress(argv[2], argv[3]);
            break;
        default:
            fprintf(stderr, "ERROR: Invalid option, choose 'c' or 'd'.\n");
            exit(EXIT_FAILURE);
            break;
    }
    return 0;
}

void decompress(char const *fname_in, char const *fname_out) {
    int i;
    HuffmanTree *ht, *hn;
    Buffer *buffer_in, *buffer_out;
    Queue *q;
    char c, byte[8], mask[8];
    uint8_t v;

    buffer_in  = buffer_create(fname_in, 'r');
    buffer_out = buffer_create(fname_out, 'w');

    /* Read Huffman tree */
    ht = huffman_deserialize(buffer_in);

    q = queue_create();

    /* Start queue with 16 bits so at the end we get the last two bytes */
    for(i = 0; i < 16; i++)
        queue_push(q, buffer_read(buffer_in));

    /* Run through the Huffman tree bit-by-bit */
    hn = ht;
    while(!buffer_in->empty) {
        c = queue_pop(q);
        switch(c) {
            case '0':
                hn = hn->left;
                break;
            case '1':
                hn = hn->right;
                break;
            default:
                break;
        }

        if(isleaf(hn)) {
            v = hn->value;
            buffer_write(buffer_out, v);
            hn = ht;
        }

        queue_push(q, buffer_read(buffer_in));
    }

    /* Get last correct bits by using the mask */
    for(i = 0; i < 8; i++) byte[i] = queue_pop(q);
    for(i = 0; i < 8; i++) mask[i] = queue_pop(q);

    i = 0;
    while(mask[i] == '1') {
        queue_push(q, byte[i]);
        i++;
    }

    /* Repeat decompression for the last bits */
    while(queue_length(q) > 0) {
        c = queue_pop(q);
        switch(c) {
            case '0':
                hn = hn->left;
                break;
            case '1':
                hn = hn->right;
                break;
            default:
                break;
        }

        if(isleaf(hn)) {
            v = hn->value;
            buffer_write(buffer_out, v);
            hn = ht;
        }
    }

    queue_free(q);
    buffer_close(buffer_in);
    buffer_close(buffer_out);
}

/* Create a Huffman tree from its serialized representation in buffer 'b' */
HuffmanTree* huffman_deserialize(Buffer *b) {
    int i;
    char c, value[9];
    HuffmanTree *ht, *left, *right;

    value[8] = '\0';
    c = buffer_read(b);
    switch(c) {
        case '0':
            /* If it's not a leaf, read its children */
            left  = huffman_deserialize(b);
            right = huffman_deserialize(b);
            ht = heapnode_create(left->key + right->key, 0);
            ht->left  = left;
            ht->right = right;
            break;

        case '1':
            /* If it's a leaf, read its value */
            for(i = 0; i < 8; i++)
                value[i] = buffer_read(b);

            ht = heapnode_create(1, (uint8_t)strtol(value, NULL, 2));
            ht->left  = NULL;
            ht->right = NULL;
            break;

        default:
            fprintf(stderr, "ERROR: non-binary character read from input buffer.\n");
            exit(EXIT_FAILURE);
            break;
    }

    return ht;
}

void compress(char const *fname_in, char const *fname_out) {
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
    get_count(fname_in, count);

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
    length = huffman_codes(ht, tmp, codes);
    he = (char*)calloc(length+1, sizeof(char));

    /* Serialize the tree so we can write it to the output */
    huffman_serialize(he, ht);


    fin = fopen(fname_in, "rb");
    if(!fin) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", fname_in);
        exit(EXIT_FAILURE);
    }

    fout = fopen(fname_out, "wb");
    if(!fout) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", fname_out);
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
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", fname_in, r);
            exit(EXIT_FAILURE);
        }

        /* If output buffer is full, flush complete bytes to the output */
        for(i = 0; i < r; i++) {
            s = codes[buffer_in[i]];
            if(strlen(buffer_out) + strlen(s) > BUFFER_SIZE) {
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
    printf("Size of original file:   %ld\n", size_in);
    printf("Size of compressed file: %ld\n", size_out);
    printf("Compression: %.1f%%\n", 100*size_out/(double)size_in);


    heapnode_free(ht);
    heap_free(h);
    fclose(fin);
    fclose(fout);
}

/* Create a serialization (string of bits) of a Huffman tree */
void huffman_serialize(char *he, HuffmanTree *ht) {
    char s[20];

    if(!ht)
        return;

    if(isleaf(ht)) {
        sprintf(s, "1%s%s", nibbles[ht->value >> 4], nibbles[ht->value & 0x0F]);
        strcat(he, s);
    } else {
        strcat(he, "0");
        huffman_serialize(he, ht->left);
        huffman_serialize(he, ht->right);
    }
}

/* Write all complete bytes in string "output" to the file "file",
keeping only the remaining bits in the string */
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

        buffer[offset] = (uint8_t)strtol(s, NULL, 2);
        offset += 1;
    }

}

/* Store the associated code of each leaf in a Huffman tree, also returning
the length of the tree's serialization */
int huffman_codes(HuffmanTree *ht, char code[MAX], char codes[256][MAX]) {
    int length;
    char left[MAX], right[MAX];

    if(!ht)
        return 0;

    if(isleaf(ht)) {
        strcpy(codes[ht->value], code);
        length = 9;
    } else {
        length = 1;

        strcpy(left, code);
        strcat(left, "0");
        length += huffman_codes(ht->left, left, codes);

        strcpy(right, code);
        strcat(right, "1");
        length += huffman_codes(ht->right, right, codes);
    }

    return length;
}

/* Check if a given node in a Huffman tree is a leaf */
bool isleaf(HuffmanTree *ht) {
    if(!ht)
        return false;
    else
        return !ht->left && !ht->right;
}

/* Generate a Huffman tree from nodes in a heap */
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

/* Get the number of occurrences of each byte in file "filename" */
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
            count[buffer[i]] += 1;
        }

        if(feof(file)) break;
    }
    fclose(file);
}

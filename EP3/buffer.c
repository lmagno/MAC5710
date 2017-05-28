#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
const char *bits[16] = {
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

typedef struct {
    uint8_t bytes[BUFFER_SIZE];
    char string[8*BUFFER_SIZE+1];
    size_t r, offset;
    FILE *file;
    bool empty;
} Buffer;

Buffer* buffer_create(char const *filename) {
    Buffer *b;

    b = (Buffer*)malloc(sizeof(Buffer));

    b->file = fopen(filename, "rb");
    if(!b->file) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    b->r = 0;
    b->offset = 0;
    b->string[0] = '\0';
    b->empty = false;

    return b;
}

void bytes2str(char *string, uint8_t *bytes, size_t r) {
    size_t i;
    uint8_t byte;

    string[0] = '\0';
    for(i = 0; i < r; i++) {
        byte = bytes[i];
        strcat(string, bits[byte >> 4]);
        strcat(string, bits[byte & 0x0F]);
    }
}

void buffer_read(Buffer *b) {
    b->r = fread(b->bytes, sizeof(uint8_t), BUFFER_SIZE, b->file);
    if(ferror(b->file)) {
        fprintf(stderr, "ERROR: Couldn't read from file, fscanf returned %ld.\n", b->r);
        exit(EXIT_FAILURE);
    }

    bytes2str(b->string, b->bytes, b->r);
}

char buffer_consume(Buffer *b) {
    char c;

    if(b->empty) {
        fprintf(stderr, "ERROR: Buffer is empty, can't consume.\n");
        exit(EXIT_FAILURE);
    }

    if(b->r == 0)
        buffer_read(b);

    c = b->string[b->offset++];
    if(b->offset == strlen(b->string)) {
        if(feof(b->file)) {
            b->empty = true;
        } else {
            buffer_read(b);
            b->offset = 0;
        }
    }

    return c;
}

void buffer_close(Buffer *b) {
    fclose(b->file);
    free(b);
}

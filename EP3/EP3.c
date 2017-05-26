#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "heap.c"

#define BUFFER_SIZE 256
int main(int argc, char const *argv[]) {
    uint8_t buffer[BUFFER_SIZE];
    int i, r, count[256];
    FILE *file;
    Heap *h;
    HeapNode hn;

    for(i = 0; i < 256; i++)
        count[i] = 0;

    file = fopen(argv[1], "rb");
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while(1) {
        r = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, file);
        if(ferror(file)) {
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", argv[1], r);
            exit(EXIT_FAILURE);
        }

        for(i = 0; i < r; i++) {
            printf("%x\n", buffer[i]);
            count[buffer[i]] += 1;
        }

        if(feof(file)) break;
    }

    h = heap_create(256);
    for(i = 0; i < 256; i++) {
        if(count[i] == 0)
            continue;

        hn = (HeapNode){ .key = (uint32_t)count[i], .value = (uint8_t)i };
        heap_push(h, hn);
    }

    while(h->size > 0) {
        hn = heap_pop(h);
        printf("%x %d\n", hn.value, hn.key);
    }
    return 0;
}

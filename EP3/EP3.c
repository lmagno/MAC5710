#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BUFFER_SIZE 256
int main(int argc, char const *argv[]) {
    uint8_t buffer[BUFFER_SIZE];
    int i, r, count[256];
    FILE *file;

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

        for(i = 0; i < 256; i++)
            printf("%d ", count[i]);

        printf("\n");
        if(feof(file)) break;
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "sequence.c"

FILE* sfopen(char const *filename, char const *mode) {
    FILE *file;

    file = fopen(filename, mode);
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}


void input(char const *filename) {
    int len = 80;
    char line[len+1];
    FILE *file;
    Sequence *s1, *s2;

    file = sfopen(filename, "r");

    // while(1) {
    //     fgets(line, len, file);
    //
    //     if(feof(file))
    //         break;
    //
    //     printf("%s\n", line);
    // }

    s1 = sequence_read(file);
    s2 = sequence_read(file);

    sequence_print(s1);
    printf("\n\n");
    sequence_print(s2);

    sequence_free(s1);
    sequence_free(s2);
    fclose(file);
}

int main(int argc, char const *argv[]) {

    input(argv[1]);
    return 0;
}

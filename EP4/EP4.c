#include <stdio.h>
#include <stdlib.h>
#include "sequence.c"
#include "grid.c"

FILE* sfopen(char const *filename, char const *mode) {
    FILE *file;

    file = fopen(filename, mode);
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}


void input(char const *filename, Sequence **s1_ptr, Sequence **s2_ptr) {
    FILE *file;
    Sequence *s1, *s2;

    file = sfopen(filename, "r");

    s1 = sequence_read(file);
    s2 = sequence_read(file);

    fclose(file);

    *s1_ptr = s1;
    *s2_ptr = s2;
}


int main(int argc, char const *argv[]) {
    Sequence *s1, *s2;
    Grid *g;
    int gap;

    gap = atoi(argv[1]);

    input(argv[2], &s1, &s2);

    printf("Strings:\n");
    printf("  %s\n\n", s1->string);
    printf("  %s\n\n", s2->string);

    g = grid_create(s1, s2);

    grid_fill(g, gap);
    
    grid_matches(g);
    grid_free(g);

    return 0;
}

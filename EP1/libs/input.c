#include <stdio.h>
#include <stdlib.h>
#include "input.h"

// Load input data from file 'filename'
Input* fileload(const char *filename) {
    int i, j, v;
    int rows, cols;
    FILE *file = NULL;
    Input *I;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "ERROR: Could not open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    I = (Input*)malloc(sizeof(Input));

    fscanf(file, "%d %d", &(I->ti), &(I->tj));
    fscanf(file, "%d %d", &(I->si), &(I->sj));
    fscanf(file, "%d %d", &rows, &cols);

    I->g = graph_create(rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(file, "%d", &v);
            if(v == 0)
                I->g->nodes[i][j] = node_create();
        }
    }

    fclose(file);
    return I;
}

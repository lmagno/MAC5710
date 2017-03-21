#include <stdio.h>
#include "matrix.h"

Matrix matrix_create(int rows, int cols) {
    Matrix M;
    int i;

    M.rows = rows;
    M.cols = cols;

    M.M = malloc(rows*sizeof(int*));
    for (i = 0; i < rows; i++) M.M[i] = malloc(cols*sizeof(int));

    return M;
}

void matrix_free(Matrix M) {
    int i;

    for (i = 0; i < M.rows; i++) free(M.M[i]);

    free(M.M);
}

void matrix_print(Matrix M) {
    int i, j;

    printf("\n  ");
    for (j = 0; j < M.cols; j++) printf("%3d", j);
    printf("\n\n");
    for (i = 0; i < M.rows; i++) {
        printf("%d ", i);
        for (j = 0; j < M.cols; j++)
            printf("%3d", M.M[i][j]);

        printf("\n");
    }
}

void matrix_prettyprint(Matrix M) {
    int i, j;

    printf("\n  ");
    for (j = 0; j < M.cols; j++) printf("%3d", j);
    printf("\n\n");
    for (i = 0; i < M.rows; i++) {
        printf("%d ", i);
        for (j = 0; j < M.cols; j++) {
            if (M.M[i][j] == 0)
                printf("   ");
            else
                printf("███");
        }

        printf("\n");
    }
}

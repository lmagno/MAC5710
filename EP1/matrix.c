#include <stdio.h>
#include "matrix.h"

// Allocate a matrix 'M' with size rows × cols
Matrix* mcreate(int rows, int cols) {
    Matrix *M;
    int i;

    M = (Matrix*)malloc(sizeof(Matrix));
    M->rows = rows;
    M->cols = cols;

    M->M = (int**)malloc(rows*sizeof(int*));
    for (i = 0; i < rows; i++)
        M->M[i] = (int*)malloc(cols*sizeof(int));

    return M;
}

// Deallocate the matrix 'M'
void mfree(Matrix *M) {
    int i;

    for (i = 0; i < M->rows; i++) free(M->M[i]);

    free(M->M);
}

// Print a representation of the matrix 'M' to STDOUT
void mprint(Matrix *M) {
    int i, j;

    printf("\n  ");
    for (j = 0; j < M->cols; j++) printf("%3d", j);
    printf("\n\n");
    for (i = 0; i < M->rows; i++) {
        printf("%d ", i);
        for (j = 0; j < M->cols; j++)
            printf("%3d", M->M[i][j]);

        printf("\n");
    }
}

// Print a representation of the matrix 'M',
// interpreted as a maze, to STDOUT
void mprettyprint(Matrix *M) {
    int i, j;

    printf("\n  ");
    for (j = 0; j < M->cols; j++) printf("%3d", j);
    printf("\n\n");
    for (i = 0; i < M->rows; i++) {
        printf("%d ", i);
        for (j = 0; j < M->cols; j++) {
            if (M->M[i][j] == 0)
                printf("   ");
            else
                printf("███");
        }

        printf("\n");
    }
}

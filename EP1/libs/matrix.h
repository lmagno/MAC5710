#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **M;
    int rows, cols;
} Matrix;

Matrix* mcreate(int rows, int cols);
Matrix* mloadname(char const *filename);
Matrix* mloadfile(FILE *file);
int mget(Matrix *M, int i, int j);
void mset(Matrix *M, int i, int j, int c);
void mfree(Matrix *M);
void mprint(Matrix *M);
void mprettyprint(Matrix *M);

#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double **M;
    int rows, cols;
} Matrix;

Matrix matrix(int rows, int cols);

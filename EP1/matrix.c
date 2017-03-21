#include <stdio.h>
#include "matrix.h"

Matrix matrix(int rows, int cols) {
    Matrix M;
    int i;

    M.M = malloc(rows*sizeof(double*));
    for (i = 0; i < rows; i++) M.M[i] = malloc(cols*sizeof(double));

    return M;
}

#include <stdio.h>
#include "matrix.h"

int main() {
    Matrix M;

    M = matrix_create(10, 11);
    printf("█\n");
    M.M[5][5] = -1;
    M.M[1][5] = -1;
    M.M[3][9] = -1;
    M.M[2][7] = -1;
    M.M[3][6] = -1;

    matrix_print(M);
    matrix_prettyprint(M);
    matrix_free(M);
    return 0;
}

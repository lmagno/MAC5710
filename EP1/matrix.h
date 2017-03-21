#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **M;
    int rows, cols;
} Matrix;


Matrix matrix_create(int rows, int cols);
void matrix_free(Matrix M);
void matrix_print(Matrix M);
void matrix_prettyprint(Matrix M);

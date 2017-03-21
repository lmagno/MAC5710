#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **M;
    int rows, cols;
} Matrix;


Matrix* mcreate(int rows, int cols);
void mfree(Matrix *M);
void mprint(Matrix *M);
void mprettyprint(Matrix *M);

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **M;
    int rows, cols;
} Matrix;


Matrix* mcreate(int rows, int cols);
Matrix* mload(char *filename);
Matrix* mloadopen(FILE *file);
void mfree(Matrix *M);
void mprint(Matrix *M);
void mprettyprint(Matrix *M);

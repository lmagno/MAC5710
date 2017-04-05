#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* #define TRUE 1*/
/* #define FALSE 0*/

typedef struct _Node {
    int i, j;
    int dist;
    bool marked, shortest;
} Node;

typedef struct _Matrix {
    int rows, cols;
    int ti, tj;
    int si, sj;
    Node ***nodes;
} Matrix;

Node*  node_create();
Node** node_neighbors(Matrix *m, Node *n, int *nlen);
Matrix* matrix_create(int rows, int cols);
void   matrix_free(Matrix *m);
void   matrix_print(Matrix *m);
void   matrix_print_dist(Matrix *m);
Matrix* matrix_load(const char *filename);
void   matrix_unmark_nodes(Matrix *m);

#endif

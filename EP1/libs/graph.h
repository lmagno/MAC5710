#ifndef GRAPH_H
#define GRAPH_H

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

typedef struct _Graph {
    int rows, cols;
    int ti, tj;
    int si, sj;
    Node ***nodes;
} Graph;

Node*  node_create();
Node** node_neighbors(Graph *g, Node *n, int *nlen);
Graph* graph_create(int rows, int cols);
void   graph_free(Graph *g);
void   graph_print(Graph *g);
void   graph_print_dist(Graph *g);
Graph* graph_load(const char *filename);
void   graph_unmark_nodes(Graph *g);

#endif

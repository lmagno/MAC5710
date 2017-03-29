#include "graph.h"

Node* node_create() {
    Node *n;

    n = (Node*)malloc(sizeof(Node));

    n->dist = INT_MAX;
    n->shortest = false;

    return n;
}

Graph* graph_create(int rows, int cols) {
    int i;
    Graph *g;

    g = (Graph*)malloc(sizeof(Graph));

    g->rows = rows;
    g->cols = cols;

    g->nodes = (Node***)malloc(rows*sizeof(Node**));

    for(i = 0; i < rows; i++)
        g->nodes[i] = (Node**)calloc(cols, sizeof(Node*));

    return g;
}

void graph_free(Graph *g) {
    int i, j;

    for(i = 0; i < g->rows; i++) {
        for(j = 0; j < g->cols; j++) free(g->nodes[i][j]);
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
}

Node** node_neighbors(Graph *g, int i, int j, int *nlen) {
    Node **neighbors;

    if(i < 0 || j < 0 || i >= g->rows || i >= g->cols) {
        fprintf(stderr, "ERROR: Index Out-of-bounds. Graph has dimensions (%d, %d), can't get node at (%d, %d).\n", g->rows, g->cols, i, j);
        exit(EXIT_FAILURE);
    }

    neighbors = (Node**)calloc(4, sizeof(Node*));

    *nlen = 0;
    if(i-1 >= 0       && g->nodes[i-1][j]) neighbors[*nlen++] = g->nodes[i-1][j];
    if(j-1 >= 0       && g->nodes[i][j-1]) neighbors[*nlen++] = g->nodes[i][j-1];
    if(i+1 <  g->rows && g->nodes[i+1][j]) neighbors[*nlen++] = g->nodes[i+1][j];
    if(j+1 <  g->cols && g->nodes[i][j+1]) neighbors[*nlen++] = g->nodes[i][j+1];

    return neighbors;
}

void graph_print(Graph *g) {
    int i, j;
    Node *n;

    printf("   ");
    for(j = 0; j < g->cols; j++) printf("%3d", j);
    printf("\n");

    for(i = 0; i < g->rows; i++) {
        printf("%3d", i);
        for(j = 0; j < g->cols; j++) {
            n = g->nodes[i][j];
            if(!n)
                printf("███");
            else if (n->shortest)
                printf(" * ");
            else
                printf("   ");
        }
        printf("\n");
    }
}

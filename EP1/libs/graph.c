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

// Load graph data from file 'filename'
Graph* graph_load(const char *filename) {
    int i, j, v;
    int ti, tj;
    int si, sj;
    int rows, cols;
    Graph *g;
    FILE *file = NULL;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "ERROR: Could not open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &ti, &tj);
    fscanf(file, "%d %d", &si, &sj);
    fscanf(file, "%d %d", &rows, &cols);

    if (ti < 0 || tj < 0 || ti >= rows || tj >= cols) {
        fprintf(stderr, "ERROR: Start index out-of-bounds.\n");
        fprintf(stderr, "\tIndex = (%d, %d).\n", ti, tj);
        fprintf(stderr, "\tGraph dimensions = (%d, %d).\n", rows, cols);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (si < 0 || sj < 0 || si >= rows || sj >= cols) {
        fprintf(stderr, "ERROR: End index out-of-bounds.\n");
        fprintf(stderr, "\tIndex = (%d, %d).\n", si, sj);
        fprintf(stderr, "\tGraph dimensions = (%d, %d).\n", rows, cols);
        fclose(file);
        exit(EXIT_FAILURE);
    }


    g = graph_create(rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(file, "%d", &v);
            if(v == 0)
                g->nodes[i][j] = node_create();
        }
    }

    fclose(file);

    if(!g->nodes[ti][tj]) {
        fprintf(stderr, "ERROR: Start index (%d, %d) is a wall.\n", ti, tj);
        exit(EXIT_FAILURE);
    }

    if(!g->nodes[si][sj]) {
        fprintf(stderr, "ERROR: End index (%d, %d) is a wall.\n", si, sj);
        exit(EXIT_FAILURE);
    }

    g->ti = ti;
    g->tj = tj;
    g->si = si;
    g->sj = sj;

    return g;
}

#include "graph.h"

Node* node_create(int i, int j) {
    Node *n;

    n = (Node*)malloc(sizeof(Node));

    n->i = i;
    n->j = j;
    n->dist = INT_MAX;
    n->shortest = false;
    n->marked = false;

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

Node** node_neighbors(Graph *g, Node *n, int *nlen) {
    int i = n->i;
    int j = n->j;
    int k;
    Node **neighbors;

    if(i < 0 || j < 0 || i >= g->rows || i >= g->cols) {
        fprintf(stderr, "ERROR: Index Out-of-bounds. Graph has dimensions (%d, %d), can't get node at (%d, %d).\n", g->rows, g->cols, i, j);
        exit(EXIT_FAILURE);
    }

    neighbors = (Node**)calloc(4, sizeof(Node*));

    k = 0;
    if(i-1 >= 0       && g->nodes[i-1][j]) neighbors[k++] = g->nodes[i-1][j];
    if(j-1 >= 0       && g->nodes[i][j-1]) neighbors[k++] = g->nodes[i][j-1];
    if(i+1 <  g->rows && g->nodes[i+1][j]) neighbors[k++] = g->nodes[i+1][j];
    if(j+1 <  g->cols && g->nodes[i][j+1]) neighbors[k++] = g->nodes[i][j+1];

    *nlen = k;
    return neighbors;
}

void graph_print(Graph *g) {
    int i, j;
    // int dx, dy;
    Node *n;
    Node *nleft, *nright, *nup, *ndown;
    bool left, right, up, down;

    // dx = g->ti - g->si;
    // dy = g->tj - g->sj;

    printf("\n");
    printf("     ");
    for(j = 0; j < g->cols; j++) printf("%3d", j);
    printf("\n");
    printf("       ");
    for(j = 0; j < g->cols; j++) printf("̅ ̅ ̅ ");
    printf("\n");

    for(i = 0; i < g->rows; i++) {
        printf("%3d⎸ ", i);
        for(j = 0; j < g->cols; j++) {
            n = g->nodes[i][j];

            if(!n)
                printf("███");
            else if(i == g->ti && j == g->tj)
                printf(" t ");
            else if(i == g->si && j == g->sj)
                printf(" s ");
            else if(n->dist == INT_MAX)
                printf("░░░");
            else if (!n->shortest)
                printf("   ");
            else {
                nleft = nright = nup = ndown = NULL;
                left  =  right =  up =  down = false;

                // Get the neighboring nodes
                if(j-1 >= 0)       nleft = g->nodes[i][j-1];
                if(i-1 >= 0)         nup = g->nodes[i-1][j];
                if(j+1 < g->cols) nright = g->nodes[i][j+1];
                if(i+1 < g->rows)  ndown = g->nodes[i+1][j];

                // Get which will lead along a shortest path to the end point
                if(nleft  &&  nleft->shortest && ( nleft->dist > n->dist))  left = true;
                if(nright && nright->shortest && (nright->dist > n->dist)) right = true;
                if(nup    &&    nup->shortest && (   nup->dist > n->dist))    up = true;
                if(ndown  &&  ndown->shortest && ( ndown->dist > n->dist))  down = true;


                // Print accordingly
                if(left)
                    printf("←");
                else
                    printf(" ");

                if(up && down)
                    printf("↕");
                else if (up)
                    printf("↑");
                else if (down)
                    printf("↓");
                else
                    printf(" ");

                if(right)
                    printf("→");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}

void graph_print_dist(Graph *g) {
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
            else if(i == g->ti && j == g->tj)
                printf(" t ");
            else if(i == g->si && j == g->sj)
                printf(" s ");
            else if (n->dist == INT_MAX)
                printf(" ∞ ");
            else
                printf("%3d", n->dist);
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
                g->nodes[i][j] = node_create(i, j);
        }
    }

    fclose(file);

    if(ti == si && tj == sj) {
        fprintf(stderr, "ERROR: Start and end index are the same: (%d, %d).\n", ti, tj);
        exit(EXIT_FAILURE);
    }

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

// Unmark all nodes of the graph 'g'
void graph_unmark_nodes(Graph *g) {
    int i, j;
    Node *n;

    for(i = 0; i < g->rows; i++) {
        for(j = 0; j < g->cols; j++) {
            n = g->nodes[i][j];
            if(n)
                n->marked = false;
        }
    }
}

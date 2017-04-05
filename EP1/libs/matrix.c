#include "matrix.h"

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

Matrix* matrix_create(int rows, int cols) {
    int i;
    Matrix *m;

    m = (Matrix*)malloc(sizeof(Matrix));

    m->rows = rows;
    m->cols = cols;

    m->nodes = (Node***)malloc(rows*sizeof(Node**));

    for(i = 0; i < rows; i++)
        m->nodes[i] = (Node**)calloc(cols, sizeof(Node*));

    return m;
}

void matrix_free(Matrix *m) {
    int i, j;

    for(i = 0; i < m->rows; i++) {
        for(j = 0; j < m->cols; j++) free(m->nodes[i][j]);
        free(m->nodes[i]);
    }
    free(m->nodes);
    free(m);
}

Node** node_neighbors(Matrix *m, Node *n, int *nlen) {
    int i = n->i;
    int j = n->j;
    int k;
    Node **neighbors;

    if(i < 0 || j < 0 || i >= m->rows || i >= m->cols) {
        fprintf(stderr, "ERROR: Index Out-of-bounds. Matrix has dimensions (%d, %d), can't get node at (%d, %d).\n", m->rows, m->cols, i, j);
        exit(EXIT_FAILURE);
    }

    neighbors = (Node**)calloc(4, sizeof(Node*));

    k = 0;
    if(i-1 >= 0       && m->nodes[i-1][j]) neighbors[k++] = m->nodes[i-1][j];
    if(j-1 >= 0       && m->nodes[i][j-1]) neighbors[k++] = m->nodes[i][j-1];
    if(i+1 <  m->rows && m->nodes[i+1][j]) neighbors[k++] = m->nodes[i+1][j];
    if(j+1 <  m->cols && m->nodes[i][j+1]) neighbors[k++] = m->nodes[i][j+1];

    *nlen = k;
    return neighbors;
}

void matrix_print(Matrix *m) {
    int i, j;
    /* int dx, dy;*/
    Node *n;
    Node *nleft, *nright, *nup, *ndown;
    bool left, right, up, down;

    /* dx = m->ti - m->si;*/
    /* dy = m->tj - m->sj;*/

    printf("\n");
    printf("     ");
    for(j = 0; j < m->cols; j++) printf("%-3d", j);
    printf("\n");
    /* printf("       ");*/
    /* for(j = 0; j < m->cols; j++) printf("̅ ̅ ̅ ");*/
    /* printf("\n");*/

    for(i = 0; i < m->rows; i++) {
        printf("%3d ", i);
        for(j = 0; j < m->cols; j++) {
            n = m->nodes[i][j];

            if(!n)
                printf("███");
            else if(i == m->ti && j == m->tj)
                printf(" t ");
            else if(i == m->si && j == m->sj)
                printf(" s ");
            else if(n->dist == INT_MAX)
                printf("░░░");
            else if (!n->shortest)
                printf("   ");
            else {
                nleft = nright = nup = ndown = NULL;
                left  =  right =  up =  down = false;

                /* Get the neighboring nodes*/
                if(j-1 >= 0)       nleft = m->nodes[i][j-1];
                if(i-1 >= 0)         nup = m->nodes[i-1][j];
                if(j+1 < m->cols) nright = m->nodes[i][j+1];
                if(i+1 < m->rows)  ndown = m->nodes[i+1][j];

                /* Get which will lead along a shortest path to the end point*/
                if(nleft  &&  nleft->shortest && ( nleft->dist > n->dist))  left = true;
                if(nright && nright->shortest && (nright->dist > n->dist)) right = true;
                if(nup    &&    nup->shortest && (   nup->dist > n->dist))    up = true;
                if(ndown  &&  ndown->shortest && ( ndown->dist > n->dist))  down = true;


                /* Print accordingly*/
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

void matrix_print_dist(Matrix *m) {
    int i, j;
    Node *n;

    printf("   ");
    for(j = 0; j < m->cols; j++) printf("%3d", j);
    printf("\n");

    for(i = 0; i < m->rows; i++) {
        printf("%3d", i);
        for(j = 0; j < m->cols; j++) {
            n = m->nodes[i][j];

            if(!n)
                printf("███");
            else if(i == m->ti && j == m->tj)
                printf(" t ");
            else if(i == m->si && j == m->sj)
                printf(" s ");
            else if (n->dist == INT_MAX)
                printf(" ∞ ");
            else
                printf("%3d", n->dist);
        }
        printf("\n");
    }
}

/* Load matrix data from file 'filename'*/
Matrix* matrix_load(const char *filename) {
    int i, j, v;
    int ti, tj;
    int si, sj;
    int rows, cols;

    Matrix *m;
    FILE *file = NULL;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "ERROR: Could not open file '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    if(fscanf(file, "%d %d", &ti, &tj) != 2) {
        fprintf(stderr, "ERROR: While reading input file %s.", filename);
        exit(EXIT_FAILURE);
    }
    if(fscanf(file, "%d %d", &si, &sj) != 2) {
        fprintf(stderr, "ERROR: While reading input file %s.", filename);
        exit(EXIT_FAILURE);
    }
    if(fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "ERROR: While reading input file %s.", filename);
        exit(EXIT_FAILURE);
    }

    if (ti < 0 || tj < 0 || ti >= rows || tj >= cols) {
        fprintf(stderr, "ERROR: Start index out-of-bounds.\n");
        fprintf(stderr, "\tIndex = (%d, %d).\n", ti, tj);
        fprintf(stderr, "\tMatrix dimensions = (%d, %d).\n", rows, cols);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (si < 0 || sj < 0 || si >= rows || sj >= cols) {
        fprintf(stderr, "ERROR: End index out-of-bounds.\n");
        fprintf(stderr, "\tIndex = (%d, %d).\n", si, sj);
        fprintf(stderr, "\tMatrix dimensions = (%d, %d).\n", rows, cols);
        fclose(file);
        exit(EXIT_FAILURE);
    }


    m = matrix_create(rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if(fscanf(file, "%d", &v) != 1) {
                fprintf(stderr, "ERROR: While reading file %s.", filename);
                exit(EXIT_FAILURE);
            }
            if(v == 0)
                m->nodes[i][j] = node_create(i, j);
        }
    }

    fclose(file);

    if(ti == si && tj == sj) {
        fprintf(stderr, "ERROR: Start and end index are the same: (%d, %d).\n", ti, tj);
        exit(EXIT_FAILURE);
    }

    if(!m->nodes[ti][tj]) {
        fprintf(stderr, "ERROR: Start index (%d, %d) is a wall.\n", ti, tj);
        exit(EXIT_FAILURE);
    }

    if(!m->nodes[si][sj]) {
        fprintf(stderr, "ERROR: End index (%d, %d) is a wall.\n", si, sj);
        exit(EXIT_FAILURE);
    }

    m->ti = ti;
    m->tj = tj;
    m->si = si;
    m->sj = sj;

    return m;
}

/* Unmark all nodes of the matrix 'g'*/
void matrix_unmark_nodes(Matrix *m) {
    int i, j;
    Node *n;

    for(i = 0; i < m->rows; i++) {
        for(j = 0; j < m->cols; j++) {
            n = m->nodes[i][j];
            if(n)
                n->marked = false;
        }
    }
}

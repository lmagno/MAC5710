#ifndef GRID_C
#define GRID_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sequence.c"

typedef struct {
    int value;
    bool top;
    bool left;
    bool diag;
} GCell;

typedef struct {
    Sequence *s1, *s2;
    GCell ***matrix;
} Grid;

/* Create a cell for the grid */
GCell* gcell_create() {
    GCell *gc;

    gc = (GCell*)malloc(sizeof(GCell));

    gc->value = 0;
    gc->top   = false;
    gc->left  = false;
    gc->diag  = false;

    return gc;
}

/* Create Grid for Needleman-Wunsch algorithm and fill the headers (and the rest with zeros)*/
Grid* grid_create(Sequence *s1, Sequence *s2) {
    Grid *g;
    int i, j;

    g = (Grid*)malloc(sizeof(Grid));

    g->s1 = s1;
    g->s2 = s2;

    /* Allocate the whole grid */
    g->matrix = (GCell***)malloc((s1->len+2)*sizeof(GCell**));
    for(i = 0; i < s1->len+2; i++) {
        g->matrix[i] = (GCell**)malloc((s2->len+2)*sizeof(GCell*));

        /* Allocate each cell */
        for(j = 0; j < s2->len+2; j++)
            g->matrix[i][j] = gcell_create();
    }

    for(i = 0; i < s1->len; i++)
        g->matrix[i+2][0]->value = s1->string[i] - 'A';

    for(j = 0; j < s2->len; j++)
        g->matrix[0][j+2]->value = s2->string[j] - 'A';

    return g;
}

/* Fill the rest of the Grid */
void grid_fill(Grid *g, int match, int mismatch, int indel) {
    int i, j;
    int t, l, d, max; /* top, left and diagonal values*/
    int l1 = g->s1->len, l2 = g->s1->len;
    GCell ***m = g->matrix;

    /* Fill the gap column */
    for(i = 0; i < l1; i++) {
        m[i+2][1]->value = (i+1)*indel;
        m[i+2][1]->top = true;
    }

    /* Fill the gap row */
    for(j = 0; j < l2; j++) {
        m[1][j+2]->value = (j+1)*indel;
        m[1][j+2]->left = true;
    }

    /* Fill the rest */
    for(i = 2; i < l1+2; i++) {
        for(j = 2; j < l2+2; j++) {
            /* Get possible scores */
            t = m[i-1][j]->value + indel;
            l = m[i][j-1]->value + indel;

            d = m[i-1][j-1]->value;
            if(m[i][0]->value == m[0][j]->value)
                d += match;
            else
                d += mismatch;

            /* Get maximum score */
            max = t;
            max = l > max ? l : max;
            max = d > max ? d : max;

            /* Fill current cell */
            m[i][j]-> value = max;
            m[i][j]->top  = (t == max);
            m[i][j]->left = (l == max);
            m[i][j]->diag = (d == max);
        }
    }
}


void grid_print(Grid *g) {
    int i, j;

    printf("        ");
    for(j = 2; j < g->s1->len+2; j++)
        printf("%4c", g->matrix[0][j]->value + 'A');
    printf("\n");

    for(i = 1; i < g->s1->len+2; i++) {
        if(i == 1)
            printf("    ");
        else
            printf("%4c", g->matrix[i][0]->value + 'A');
            
        for(j = 1; j < g->s2->len+2; j++) {
            printf("%4d", g->matrix[i][j]->value);
        }
        printf("\n");
    }
    printf("\n");
}

void grid_printarrows(Grid *g) {
    int i, j;

    printf("        ");
    for(j = 2; j < g->s1->len+2; j++)
        printf("%4c", g->matrix[0][j]->value + 'A');
    printf("\n");

    for(i = 1; i < g->s1->len+2; i++) {
        if(i == 1)
            printf("    ");
        else
            printf("%4c", g->matrix[i][0]->value + 'A');

        for(j = 1; j < g->s2->len+2; j++) {
            printf(" ");

            if(g->matrix[i][j]->left)
                printf("←");
            else
                printf(" ");

            if(g->matrix[i][j]->diag)
                printf("↖");
            else
                printf(" ");

            if(g->matrix[i][j]->top)
                printf("↑");
            else
                printf(" ");


        }
        printf("\n");
    }
    printf("\n");
}

void grid_free(Grid *g) {
    int i;

    for(i = 0; i < g->s1->len+2; i++)
        free(g->matrix[i]);

    free(g->matrix);

    sequence_free(g->s1);
    sequence_free(g->s2);

    free(g);
}

#endif

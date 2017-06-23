#ifndef GRID_C
#define GRID_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sequence.c"

const int blosum62[26][26] = {
    { 4, -2,  0, -2, -1, -2,  0, -2, -1, -1, -1, -1, -1, -2,  0, -1, -1, -1,  1,  0,  0,  0, -3,  0, -2, -1},
    {-2,  4, -3,  4,  1, -3, -1,  0, -3, -4,  0, -4, -3,  3, -1, -2,  0, -1,  0, -1, -1, -3, -4, -1, -3,  1},
    { 0, -3,  9, -3, -4, -2, -3, -3, -1, -1, -3, -1, -1, -3, -2, -3, -3, -3, -1, -1, -2, -1, -2, -2, -2, -3},
    {-2,  4, -3,  6,  2, -3, -1, -1, -3, -4, -1, -4, -3,  1, -1, -1,  0, -2,  0, -1, -1, -3, -4, -1, -3,  1},
    {-1,  1, -4,  2,  5, -3, -2,  0, -3, -3,  1, -3, -2,  0, -1, -1,  2,  0,  0, -1, -1, -2, -3, -1, -2,  4},
    {-2, -3, -2, -3, -3,  6, -3, -1,  0,  0, -3,  0,  0, -3, -1, -4, -3, -3, -2, -2, -1, -1,  1, -1,  3, -3},
    { 0, -1, -3, -1, -2, -3,  6, -2, -4, -4, -2, -4, -3,  0, -1, -2, -2, -2,  0, -2, -1, -3, -2, -1, -3, -2},
    {-2,  0, -3, -1,  0, -1, -2,  8, -3, -3, -1, -3, -2,  1, -1, -2,  0,  0, -1, -2, -1, -3, -2, -1,  2,  0},
    {-1, -3, -1, -3, -3,  0, -4, -3,  4,  3, -3,  2,  1, -3, -1, -3, -3, -3, -2, -1, -1,  3, -3, -1, -1, -3},
    {-1, -4, -1, -4, -3,  0, -4, -3,  3,  3, -3,  3,  2, -3, -1, -3, -3, -3, -2, -1, -1,  2, -3, -1, -1, -3},
    {-1,  0, -3, -1,  1, -3, -2, -1, -3, -3,  5, -2, -1,  0, -1, -1,  1,  2,  0, -1, -1, -2, -3, -1, -2,  1},
    {-1, -4, -1, -4, -3,  0, -4, -3,  2,  3, -2,  4,  2, -3, -1, -3, -2, -2, -2, -1, -1,  1, -2, -1, -1, -3},
    {-1, -3, -1, -3, -2,  0, -3, -2,  1,  2, -1,  2,  5, -2, -1, -2,  0, -1, -1, -1, -1,  1, -1, -1, -1, -1},
    {-2,  3, -3,  1,  0, -3,  0,  1, -3, -3,  0, -3, -2,  6, -1, -2,  0,  0,  1,  0, -1, -3, -4, -1, -2,  0},
    { 0, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1,  0,  0, -1, -1, -2, -1, -1, -1},
    {-1, -2, -3, -1, -1, -4, -2, -2, -3, -3, -1, -3, -2, -2, -2,  7, -1, -2, -1, -1, -2, -2, -4, -2, -3, -1},
    {-1,  0, -3,  0,  2, -3, -2,  0, -3, -3,  1, -2,  0,  0, -1, -1,  5,  1,  0, -1, -1, -2, -2, -1, -1,  3},
    {-1, -1, -3, -2,  0, -3, -2,  0, -3, -3,  2, -2, -1,  0, -1, -2,  1,  5, -1, -1, -1, -3, -3, -1, -2,  0},
    { 1,  0, -1,  0,  0, -2,  0, -1, -2, -2,  0, -2, -1,  1,  0, -1,  0, -1,  4,  1,  0, -2, -3,  0, -2,  0},
    { 0, -1, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1, -1,  0,  0, -1, -1, -1,  1,  5,  0,  0, -2,  0, -2, -1},
    { 0, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1,  0,  0, -1, -1, -2, -1, -1, -1},
    { 0, -3, -1, -3, -2, -1, -3, -3,  3,  2, -2,  1,  1, -3, -1, -2, -2, -3, -2,  0, -1,  4, -3, -1, -1, -2},
    {-3, -4, -2, -4, -3,  1, -2, -2, -3, -3, -3, -2, -1, -4, -2, -4, -2, -3, -3, -2, -2, -3, 11, -2,  2, -3},
    { 0, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1,  0,  0, -1, -1, -2, -1, -1, -1},
    {-2, -3, -2, -3, -2,  3, -3,  2, -1, -1, -2, -1, -1, -2, -1, -3, -1, -2, -2, -2, -1, -1,  2, -1,  7, -2},
    {-1,  1, -3,  1,  4, -3, -2,  0, -3, -3,  1, -3, -1,  0, -1, -1,  3,  0,  0, -1, -1, -2, -3, -1, -2,  4}
};

typedef struct {
    int value;
    bool top;
    bool left;
    bool diag;
} GCell;

typedef struct {
    Sequence *s1, *s2;
    GCell ***matrix;
    int score;
    int alignments;
} Grid;

void _grid_matches(Grid *g, int i, int j, char *s1, char *s2);

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
void grid_fill(Grid *g, int gap) {
    int i, j;
    int t, l, d, max; /* top, left and diagonal values*/
    int l1 = g->s1->len, l2 = g->s1->len;
    GCell ***m = g->matrix;

    /* Fill the gap column */
    for(i = 0; i < l1; i++) {
        m[i+2][1]->value = (i+1)*gap;
        m[i+2][1]->top = true;
    }

    /* Fill the gap row */
    for(j = 0; j < l2; j++) {
        m[1][j+2]->value = (j+1)*gap;
        m[1][j+2]->left = true;
    }

    /* Fill the rest */
    for(i = 2; i < l1+2; i++) {
        for(j = 2; j < l2+2; j++) {
            /* Get possible scores */
            t = m[i-1][j]->value + gap;
            l = m[i][j-1]->value + gap;

            d = m[i-1][j-1]->value + blosum62[m[i][0]->value][m[0][j]->value];

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


void grid_matches(Grid *g) {
    int l1 = g->s1->len;
    int l2 = g->s2->len;
    char *s1, *s2;

    s1 = (char*)malloc((l1+l2+1)*sizeof(char));
    s2 = (char*)malloc((l1+l2+1)*sizeof(char));

    g->score = g->matrix[l1+1][l2+1]->value;
    g->alignments = 0;
    printf("Matches:\n");
    s1[0] = s2[0] = '\0';
    _grid_matches(g, l1+1, l2+1, s1, s2);

    printf("Score: %d\n", g->score);
    printf("Number of alignments found: %d\n", g->alignments);

    free(s1);
    free(s2);
}

void _grid_matches(Grid *g, int i, int j, char *s1, char *s2) {
    GCell *gc = g->matrix[i][j];
    char c1 = g->matrix[i][0]->value + 'A';
    char c2 = g->matrix[0][j]->value + 'A';
    size_t l1 = strlen(s1);
    size_t l2 = strlen(s2);
    int k;

    if(gc->top)  {
        s1[l1] = c1;
        s2[l2] = '-';
        s1[l1+1] = '\0';
        s2[l2+1] = '\0';

        _grid_matches(g, i-1,   j, s1, s2);
    }

    if(gc->left) {
        s1[l1] = '-';
        s2[l2] = c2;
        s1[l1+1] = '\0';
        s2[l2+1] = '\0';

        _grid_matches(g,   i, j-1, s1, s2);
    }

    if(gc->diag) {
        s1[l1] = c1;
        s2[l2] = c2;
        s1[l1+1] = '\0';
        s2[l2+1] = '\0';

        _grid_matches(g, i-1, j-1, s1, s2);
    }

    l1 = strlen(s1);
    l2 = strlen(s2);
    if(i == 1 && j == 1) {
        /* Print asterisks indicating mismatches */
        printf("  ");
        for(k = 1; k <= l1; k++) {
            c1 = s1[l1-k];
            c2 = s2[l2-k];

            if(c1 != '-' && c2 != '-' && (c1 != c2))
                printf("*");
            else
                printf(" ");
        }
        printf("\n");

        /* Print first string */
        printf("  ");
        for(k = 1; k <= l1; k++) printf("%c", s1[l1-k]);
        printf("\n");

        /* Print vertical bars indicating matches */
        printf("  ");
        for(k = 1; k <= l1; k++) {
            c1 = s1[l1-k];
            c2 = s2[l2-k];

            if(c1 != '-' && c2 != '-' && (c1 == c2))
                printf("|");
            else
                printf(" ");
        }
        printf("\n");

        printf("  ");
        for(k = 1; k <= l2; k++) printf("%c", s2[l2-k]);
        printf("\n");
        printf("\n");

        g->alignments++;
    }
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

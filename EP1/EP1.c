/*****************************************************/
/* Nome: Lucas Magno                                 */
/* Número USP: 7994983                               */
/* Exercício-Programa 1                              */
/*                                                   */
/* Executar o programa da forma:                     */
/*     $ ./EP1 file1 file2 ...                       */
/*                                                   */
/* Resultados são impressos na stdout.               */
/*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "libs/matrix.h"
#include "libs/queue.h"

int  min(int a, int b);
void shortest_distances(Matrix *m);
int  shortest_paths(Matrix *m, Node *n);

int main(int argc, char **argv) {
    int i, npaths;
    Matrix *m;
    char *filename;
    Node *s;

    for(i = 1; i < argc; i++) {
        filename = argv[i];
        printf("\n\n=========================%s=========================\n", filename);

        /* Load problem */
        m = matrix_load(filename);

        /* Mark every node with its distance from the start point */
        shortest_distances(m);

        /* If the distance of the exit from the starting point is
        INT_MAX, i.e. ∞, then it is unreachable. In this case,
        there are no shortest paths to find. */
        if(s->dist == INT_MAX) {
            matrix_print(m);
            printf("The exit is unreachable.\n");
            matrix_free(m);
            continue;
        }

        /* Find all shortest paths from 's' to 't'*/
        s = m->nodes[m->si][m->sj];
        npaths = shortest_paths(m, s);
        printf("Length of shortest paths: %d\n", s->dist);
        printf("Number of shortest paths: %d\n", npaths);

        matrix_free(m);
    }

    return 0;
}

/* Simple function for calculating minimum*/
int min(int a, int b) {
    return a < b ? a : b;
}

/* Calculate the shortest distance of every node in the*/
/* matrix 'm' to the starting point 't' at index (ti, tj),*/
/* keeping the result in the appropriate field in each node.*/
void shortest_distances(Matrix *m) {
    int k;
    int ti = m->ti;
    int tj = m->tj;
    int nlen, mindist;
    Queue *q = queue_create();
    Node **neighbors, *n, *neighbor;

    /* Unmark all nodes*/
    matrix_unmark_nodes(m);

    /* Put the first node ('t') in the queue*/
    n = m->nodes[ti][tj];
    n->dist    = -1;
    n->marked  = true;

    queue_push(q, n);

    while(queue_length(q) > 0) {
        /* Take a node out of the queue*/
        n = queue_pop(q);

        /* Get the neighbors of the node 'n'*/
        neighbors = node_neighbors(m, n, &nlen);

        mindist = n->dist;
        for(k = 0; k < nlen; k++) {
            neighbor = neighbors[k];

            if(neighbor->marked) {
                /* Get the minimum distance from the starting point*/
                /* between 'n' and its neighbors marked so far*/
                mindist = min(mindist, neighbor->dist);
            } else {
                /* Mark the neighbor and put it in the queue*/
                neighbor->marked = true;

                queue_push(q, neighbor);
            }
        }
        free(neighbors);

        /* Distance from 't' to 'n' is one more than its neighbor*/
        /* who's closest to 't'*/
        n->dist = mindist + 1;
    }

    queue_free(q);
}

/* Recursively calculates the shortest paths of matrix 'm', starting at
the node 'n'. Prints to stdout every time it finds a complete shortest path,
and returns the number of complete shortest paths found from the node 'n' */
int shortest_paths(Matrix *m, Node *n) {
    int k;
    int nlen, mindist, npaths = 0;
    Node *neighbor, **neighbors;

    /* Mark this node as being part of the current shortest path */
    n->shortest = true;

    /* Get the neighbors of the current node*/
    neighbors = node_neighbors(m, n, &nlen);

    /* Get the closest a neighbor of the current node is to 't'*/
    mindist = n->dist;
    for(k = 0; k < nlen; k++) {
        neighbor = neighbors[k];
        mindist = min(mindist, neighbor->dist);
    }

    if(mindist == 0) {
        /* If 't' is a neighbor, then this path is a complete shortest path,
        so we print it and unmark it and return 1, i.e., we found one shortest
        path so far */

        matrix_print(m);
        n->shortest = false;
        return 1;
    } else {
        /* Visit all neighbors of the current that will lead to a shortest path
        summing the number of complete paths found in each */
        for(k = 0; k < nlen; k++) {
            neighbor = neighbors[k];
            if(neighbor->dist == mindist) {
                npaths += shortest_paths(m, neighbor);
            }
        }
    }

    /* Unmark the current node as being part of the current path and
    return the number of complete shortest paths found through its neighbors */
    n->shortest = false;
    return npaths;
}

#include <stdio.h>
#include <stdlib.h>
#include "libs/graph.h"
#include "libs/stack.h"
#include "libs/queue.h"

int min(int a, int b);
void coordinates_to_hash(Graph *g, int i, int j, int *hash);
void hash_to_coordinates(Graph *g, int *i, int *j, int hash);
void shortest_distances(Graph *g);
void shortest_paths(Graph *g);

int main(int argc, char **argv) {
    int i;
    Graph *g;
    char *filename;

    for(i = 1; i < argc; i++) {
        filename = argv[i];
        printf("\n\n=========================%s=========================\n", filename);
        g = graph_load(filename);
        shortest_distances(g);
        /* graph_print_dist(g);*/
        shortest_paths(g);
        graph_print(g);
        graph_free(g);
    }

    return 0;
}

/* Simple function for calculating minimum*/
int min(int a, int b) {
    return a < b ? a : b;
}

/* Functions to convert between a node's coordinates and its hash*/
/* for use in the queue*/
void coordinates_to_hash(Graph *g, int i, int j, int *hash) {
    *hash = g->cols*i + j;
}

void hash_to_coordinates(Graph *g, int *i, int *j, int hash) {
    *i = hash/g->cols;
    *j = hash%g->cols;
}

/* Calculate the shortest distance of every node in the*/
/* graph 'g' to the starting point 't' at index (ti, tj),*/
/* keeping the result in the appropriate field in each node.*/
void shortest_distances(Graph *g) {
    int i, j, k;
    int ti = g->ti;
    int tj = g->tj;
    int hash, nlen, mindist;
    Queue *q = queue_create();
    Node **neighbors, *n, *neighbor;

    /* Unmark all nodes*/
    graph_unmark_nodes(g);

    /* Put the first node ('t') in the queue*/
    n = g->nodes[ti][tj];
    n->dist    = -1;
    n->marked  = true;

    coordinates_to_hash(g, ti, tj, &hash);
    queue_push(q, hash);

    while(queue_length(q) > 0) {
        /* Take a hash out of the queue and get the corresponding node*/
        hash = queue_pop(q);
        hash_to_coordinates(g, &i, &j, hash);
        n = g->nodes[i][j];

        /* Get the neighbors of the node 'n'*/
        neighbors = node_neighbors(g, n, &nlen);

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

                coordinates_to_hash(g, neighbor->i, neighbor->j, &hash);
                queue_push(q, hash);
            }
        }
        free(neighbors);

        /* Distance from 't' to 'n' is one more than its neighbor*/
        /* who's closest to 't'*/
        n->dist = mindist + 1;
    }

    queue_free(q);
}

void shortest_paths(Graph *g) {
    int i, j, k;
    int index, nlen, mindist;
    int si = g->si;
    int sj = g->sj;
    Node *n, *neighbor, **neighbors;
    Queue *q = queue_create();


    /* Start with the end node and put it in the queue*/
    n = g->nodes[si][sj];
    n->shortest = true;
    coordinates_to_hash(g, si, sj, &index);
    queue_push(q, index);

    while(queue_length(q) > 0) {
        /* Take a hash out of the queue and get the corresponding node*/
        index = queue_pop(q);
        hash_to_coordinates(g, &i, &j, index);
        n = g->nodes[i][j];

        /* Get the neighbors of the node 'n'*/
        neighbors = node_neighbors(g, n, &nlen);

        /* Get the closest a neighbor of the node 'n' is to 't'*/
        mindist = n->dist;
        for(k = 0; k < nlen; k++) {
            neighbor = neighbors[k];
            mindist = min(mindist, neighbor->dist);
        }

        /* Mark all the neighbors of the node 'n' which are*/
        /* closest to 't' as being part of a shortest path*/
        /* and add them to the queue*/
        for(k = 0; k < nlen; k++) {
            neighbor = neighbors[k];
            if(neighbor->dist == mindist) {
                neighbor->shortest = true;

                coordinates_to_hash(g, neighbor->i, neighbor->j, &index);
                queue_push(q, index);
            }
        }
    }

    queue_free(q);
}

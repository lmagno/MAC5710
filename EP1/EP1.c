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

/* Calculate the shortest distance of every node in the*/
/* graph 'g' to the starting point 't' at index (ti, tj),*/
/* keeping the result in the appropriate field in each node.*/
void shortest_distances(Graph *g) {
    int k;
    int ti = g->ti;
    int tj = g->tj;
    int nlen, mindist;
    Queue *q = queue_create();
    Node **neighbors, *n, *neighbor;

    /* Unmark all nodes*/
    graph_unmark_nodes(g);

    /* Put the first node ('t') in the queue*/
    n = g->nodes[ti][tj];
    n->dist    = -1;
    n->marked  = true;

    queue_push(q, n);

    while(queue_length(q) > 0) {
        /* Take a node out of the queue*/
        n = queue_pop(q);

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

void shortest_paths(Graph *g) {
    int k;
    int nlen, mindist;
    int si = g->si;
    int sj = g->sj;
    Node *n, *neighbor, **neighbors;
    Queue *q = queue_create();


    /* Start with the end node and put it in the queue*/
    n = g->nodes[si][sj];
    n->shortest = true;
    queue_push(q, n);

    while(queue_length(q) > 0) {
        /* Take a node out of the queue*/
        n = queue_pop(q);

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

                queue_push(q, neighbor);
            }
        }
    }

    queue_free(q);
}

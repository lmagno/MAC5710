#include <stdio.h>
#include <stdlib.h>
#include "libs/graph.h"
#include "libs/stack.h"
#include "libs/queue.h"

int min(int a, int b);
void shortest_distances(Graph *g);
void coordinates_to_hash(Graph *g, int i, int j, int *hash);
void hash_to_coordinates(Graph *g, int *i, int *j, int hash);

int main() {
    Graph *g;

    g = graph_load("data/input.dat");
    shortest_distances(g);
    graph_print_dist(g);
    graph_free(g);
    return 0;
}

// Simple function for calculating minimum
int min(int a, int b) {
    return a < b ? a : b;
}

// Functions to convert between a node's coordinates and its hash
// for use in the queue
void coordinates_to_hash(Graph *g, int i, int j, int *hash) {
    *hash = g->cols*i + j;
}

void hash_to_coordinates(Graph *g, int *i, int *j, int hash) {
    *i = hash/g->cols;
    *j = hash%g->cols;
}

// Calculate the shortest distance of every node in the
// graph 'g' to the starting point 't' at index (ti, tj),
// keeping the result in the appropriate field in each node.
void shortest_distances(Graph *g) {
    int i, j, k;
    int ti = g->ti;
    int tj = g->tj;
    int hash, nlen, mindist;
    Queue *q = qcreate();
    Node **neighbors, *n, *neighbor;

    // Put the first node ('t') in the queue
    n = g->nodes[ti][tj];
    n->dist    = -1;
    n->marked  = true;

    coordinates_to_hash(g, ti, tj, &hash);
    qpush(q, hash);

    while(qlength(q) > 0) {
        // Take a hash out of the queue
        hash = qpop(q);
        hash_to_coordinates(g, &i, &j, hash);

        // Get the 'nlen' neighbors of the node 'n'
        n = g->nodes[i][j];
        neighbors = node_neighbors(g, n, &nlen);

        mindist = n->dist;
        for(k = 0; k < nlen; k++) {
            neighbor = neighbors[k];

            if(neighbor->marked) {
                // Get the minimum distance from the starting point
                // between 'n' and its neighbors marked so far
                mindist = min(mindist, neighbor->dist);
            } else {
                // Mark the neighbor and put it in the queue
                neighbor->marked = true;

                coordinates_to_hash(g, neighbor->i, neighbor->j, &hash);
                qpush(q, hash);
            }
        }

        // Distance from 't' to 'n' is one more than its neighbor
        // who's closest to 't'
        n->dist = mindist + 1;
    }

    qfree(q);
}

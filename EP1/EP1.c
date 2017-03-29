#include <stdio.h>
#include <stdlib.h>
#include "libs/graph.h"
#include "libs/stack.h"
#include "libs/queue.h"

int main() {
    Graph *g;
    Stack *s;
    Queue *q;

    g = graph_load("data/input.dat");

    graph_free(g);
    return 0;
}

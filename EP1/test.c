#include <stdio.h>
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/graph.h"

int main() {
    Stack *s;
    Queue *q;
    Graph *g;

    printf("=================Graph=================\n\n");
    printf("\n");
    g = graph_load("data/input.dat");

    graph_print_dist(g);
    graph_free(g);

    printf("=================Stack=================\n\n");
    s = screate();
    sprint(s);
    spush(s, 1); sprint(s);
    spush(s, 2); sprint(s);
    spush(s, 3); sprint(s);
    spush(s, -1); sprint(s);
    spop(s); sprint(s);
    spop(s); sprint(s);
    spop(s); sprint(s);
    spop(s); sprint(s);
    sfree(s);


    printf("=================Queue=================\n\n");
    q = qcreate(); qprint(q);
    qpush(q, 1); qprint(q);
    qpush(q, 2); qprint(q);
    qpush(q, 3); qprint(q);
    qpop(q); qprint(q);
    qpop(q); qprint(q);
    qpop(q); qprint(q);
    qfree(q);
    return 0;
}

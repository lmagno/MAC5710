#include <stdio.h>
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/input.h"
#include "libs/graph.h"

int main() {
    Stack *s;
    Queue *q;
    Input *I;
    Graph *g;

    printf("=================Graph=================\n\n");
    printf("\n");
    I = fileload("data/input.dat");
    printf("t = (%d, %d)\n", I->ti, I->tj);
    printf("s = (%d, %d)\n", I->si, I->sj);

    g = I->g;
    graph_print(g);
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

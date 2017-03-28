#include <stdio.h>
#include "libs/matrix.h"
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/input.h"

int main() {
    Matrix *M;
    Stack *s;
    Queue *q;
    Input *I;

    printf("=================Matrix=================\n\n");
    M = mcreate(10, 11);
    mset(M, 5, 5, -1);
    mset(M, 1, 1, -1);
    mset(M, 3, 3, -1);
    mset(M, 2, 2, -1);
    mset(M, 3, 3, -1);


    mprint(M);
    mprettyprint(M);
    mfree(M);

    printf("\n");
    I = fileload("data/input.dat");
    printf("t = (%d, %d)\n", I->ti, I->tj);
    printf("s = (%d, %d)\n", I->si, I->sj);
    mprint(I->M);
    mprettyprint(I->M);
    mfree(I->M);

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

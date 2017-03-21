#include <stdio.h>
#include "matrix.h"
#include "stack.h"
#include "queue.h"

int main() {
    Matrix M;
    Stack *s;
    Queue *q;
    M = mcreate(10, 11);
    printf("█\n");
    M.M[5][5] = -1;
    M.M[1][5] = -1;
    M.M[3][9] = -1;
    M.M[2][7] = -1;
    M.M[3][6] = -1;

    mprint(M);
    mprettyprint(M);
    mfree(M);

    s = screate(100);
    sprint(s);
    spush(s, 1);
    spush(s, 2);
    spush(s, 3);
    spush(s, -1);
    sprint(s);
    sfree(s);

    q = qcreate(100);
    qpush(q, 1);
    qpush(q, 2);
    qpush(q, 3);
    qprint(q);
    qfree(q);
    return 0;
}

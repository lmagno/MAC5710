#include <stdio.h>
#include "libs/matrix.h"
#include "libs/stack.h"
#include "libs/queue.h"

int main() {
    Matrix *M;
    Stack *s;
    Queue *q;
    FILE *file = NULL;

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

    M = mloadname("data/input.dat");
    mprint(M);
    mprettyprint(M);
    mfree(M);

    file = fopen("data/input.dat", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file '%s'.", "data/input.dat");
        exit(EXIT_FAILURE);
    }

    M = mloadfile(file);
    fclose(file);
    mprint(M);
    mprettyprint(M);
    mfree(M);

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

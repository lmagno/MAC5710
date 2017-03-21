#include <stdio.h>
#include "matrix.h"
#include "stack.h"
#include "queue.h"

int main() {
    Matrix M;
    Stack *s;
    Queue *q;

    printf("=================Matrix=================\n\n");
    M = matrix_create(10, 11);
    printf("█\n");
    M.M[5][5] = -1;
    M.M[1][5] = -1;
    M.M[3][9] = -1;
    M.M[2][7] = -1;
    M.M[3][6] = -1;

    matrix_print(M);
    matrix_prettyprint(M);
    matrix_free(M);

    printf("=================Stack=================\n\n");
    s = stack_create(100);
    stack_print(s);
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_push(s, -1);
    stack_print(s);
    stack_free(s);


    printf("=================Queue=================\n\n");
    q = queue_create(100);
    queue_push(q, 1);
    queue_push(q, 2);
    queue_push(q, 3);
    queue_print(q);
    queue_free(q);
    return 0;
}

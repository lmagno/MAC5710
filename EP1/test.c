#include <stdio.h>
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/matrix.h"

int main() {
    Stack *s;
    Queue *q;
    Matrix *m;

    printf("=================Matrix=================\n\n");
    printf("\n");
    m = matrix_load("data/input.dat");

    matrix_print_dist(m);
    matrix_free(m);

    printf("=================Stack=================\n\n");
    s = stack_create();
    stack_print(s);
    stack_push(s, 1); stack_print(s);
    stack_push(s, 2); stack_print(s);
    stack_push(s, 3); stack_print(s);
    stack_push(s, -1); stack_print(s);
    stack_pop(s); stack_print(s);
    stack_pop(s); stack_print(s);
    stack_pop(s); stack_print(s);
    stack_pop(s); stack_print(s);
    stack_free(s);


    printf("=================Queue=================\n\n");
    q = queue_create(); queue_print(q);
    queue_push(q, 1); queue_print(q);
    queue_push(q, 2); queue_print(q);
    queue_push(q, 3); queue_print(q);
    queue_pop(q); queue_print(q);
    queue_pop(q); queue_print(q);
    queue_pop(q); queue_print(q);
    queue_free(q);
    return 0;
}

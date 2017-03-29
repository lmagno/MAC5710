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

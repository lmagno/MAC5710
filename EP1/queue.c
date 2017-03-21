#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* queue_create(int maxlen) {
    Queue *q;

    q = (Queue*)malloc(sizeof(Queue));
    q->maxlen = maxlen;
    q->bottom = 0;
    q->top = 0;
    q->q = (int*)malloc(maxlen*sizeof(int));

    return q;
}

void queue_push(Queue *q, int i) {
    if (q->top == q->maxlen) {
        fprintf(stderr, "The queue is full! Cannot push into index %d.\n", q->maxlen);
        exit(EXIT_FAILURE);
    }
    q->q[q->top++] = i;
}

int queue_pop(Queue *q) {
    if (q->bottom == q->top) {
        fprintf(stderr, "The queue is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    return q->q[q->bottom++];
}

void queue_print(Queue *q) {
    int i;

    printf("\n");
    for (i = q->bottom; i < q->top; i++) printf("%4d", i);
    printf("\n");
    for (i = q->bottom; i < q->top; i++) printf("%4d", q->q[i]);
    printf("\n");
}

void queue_free(Queue *q) {
    free(q->q);
    free(q);
}

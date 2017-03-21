#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Allocate a queue 'q' with max length 'maxlen'
Queue* qcreate(int maxlen) {
    Queue *q;

    q = (Queue*)malloc(sizeof(Queue));
    q->maxlen = maxlen;
    q->bottom = 0;
    q->top = 0;
    q->q = (int*)malloc(maxlen*sizeof(int));

    return q;
}

// Push a value 'i' into the queue 'q',
// checking and exiting with error if it's full
void qpush(Queue *q, int i) {
    if (q->top == q->maxlen) {
        fprintf(stderr, "The queue is full! Cannot push into index %d.\n", q->maxlen);
        exit(EXIT_FAILURE);
    }
    q->q[q->top++] = i;
}

// Pop and return a value from the queue 'q',
// checking and exiting with failure if it's empty
int qpop(Queue *q) {
    if (q->bottom == q->top) {
        fprintf(stderr, "The queue is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    return q->q[q->bottom++];
}

// Print a representation of the queue 'q' to STDOUT
void qprint(Queue *q) {
    int i;

    printf("\n");
    for (i = q->bottom; i < q->top; i++) printf("%4d", i);
    printf("\n");
    for (i = q->bottom; i < q->top; i++) printf("%4d", q->q[i]);
    printf("\n");
}

// Deallocate the queue 'q'
void qfree(Queue *q) {
    free(q->q);
    free(q);
}

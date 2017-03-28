#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// A single cell of the queue
struct _QCell {
    int value;
    struct _QCell *next;
};


// The header of the queue
struct _Queue {
    int length;
    QCell *first;
    QCell *last;
};


// Allocate an empty queue
Queue* qcreate() {
    Queue *q;

    q = (Queue*)malloc(sizeof(Queue));

    q->length = 0;
    q->first = NULL;
    q->last  = NULL;

    return q;
}

// Push a value 'i' into the queue 'q'
void qpush(Queue *q, int i) {
    QCell *c;

    // Initalize a QCell with the value 'i'
    c = (QCell*)malloc(sizeof(QCell));
    c->value = i;
    c->next = NULL;

    // Add it to the end of the queue
    if (qlength(q) == 0) {
        q->first = c;
        q->last  = c;
    } else {
        q->last->next = c;
        q->last = c;
    }

    q->length += 1;
}

// Pop and return a value from the queue 'q',
// checking and exiting with failure if it's empty
int qpop(Queue *q) {
    int v;
    QCell *c;
    if (qlength(q) == 0) {
        fprintf(stderr, "The queue is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    // Pop first cell
    c = q->first;

    // Extract its value
    v = c->value;

    // Set the second cell as the new first
    q->first = c->next;
    q->length -= 1;

    free(c);
    return v;
}

// Print a representation of the queue 'q' to STDOUT
void qprint(Queue *q) {
    int i;
    QCell *c;

    printf("\n");
    for (i = 1; i <= qlength(q); i++) printf("%4d", i);
    printf("\n");
    for (c = q->first; c != NULL; c = c->next) printf("%4d", c->value);
    printf("\n");
}

// Deallocate the queue 'q'
void qfree(Queue *q) {
    QCell *a, *b;

    if (qlength(q) > 0) {
        a = q->first;
        b = a->next;
        while (b != NULL) {
            free(a);
            a = b;
            b = b->next;
        }
    }

    free(q);
}

// Get the length of the queue 'q'
int qlength(Queue *q) {
    return q->length;
}

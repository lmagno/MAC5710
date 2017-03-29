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
Queue* queue_create() {
    Queue *q;

    q = (Queue*)malloc(sizeof(Queue));

    q->length = 0;
    q->first = NULL;
    q->last  = NULL;

    return q;
}

// Push a value 'i' into the queue 'q'
void queue_push(Queue *q, int i) {
    QCell *c;

    // Initalize a QCell with the value 'i'
    c = (QCell*)malloc(sizeof(QCell));
    c->value = i;
    c->next = NULL;

    // Add it to the end of the queue
    if (queue_length(q) == 0) {
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
int queue_pop(Queue *q) {
    int v;
    QCell *c;

    if (queue_length(q) == 0) {
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
void queue_print(Queue *q) {
    QCell *c;

    if (queue_length(q) == 0) {
        printf("[]\n");
        return;
    }

    c = q->first;
    printf("[");
    printf("%d", c->value);
    for (c = c->next; c != NULL; c = c->next) printf(", %d", c->value);
    printf("]");
    printf("\n");
}

// Deallocate the queue 'q'
void queue_free(Queue *q) {
    QCell *a, *b;

    a = q->first;
    while (a != NULL) {
        b = a->next;
        free(a);
        a = b;
    }

    free(q);
}

// Get the length of the queue 'q'
int queue_length(Queue *q) {
    return q->length;
}

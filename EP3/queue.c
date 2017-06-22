#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

/* Allocate an empty queue*/
Queue* queue_create() {
    Queue *q;

    q = (Queue*)malloc(sizeof(Queue));

    q->length = 0;
    q->first = NULL;
    q->last  = NULL;

    return q;
}

/* Push a value 'c' into the queue 'q'*/
void queue_push(Queue *q, char c) {
    QCell *qc;

    /* Initalize a QCell with the value 'i'*/
    qc = (QCell*)malloc(sizeof(QCell));
    qc->value = c;
    qc->next = NULL;

    /* Add it to the end of the queue*/
    if (queue_length(q) == 0) {
        q->first = qc;
        q->last  = qc;
    } else {
        q->last->next = qc;
        q->last = qc;
    }

    q->length += 1;
}

/* Pop and return a value from the queue 'q',*/
/* checking and exiting with failure if it's empty*/
char queue_pop(Queue *q) {
    QCell *qc;
    char c;

    if (queue_length(q) == 0) {
        fprintf(stderr, "The queue is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    /* Pop first cell*/
    qc = q->first;

    /* Extract its value*/
    c = qc->value;

    /* Set the second cell as the new first*/
    q->first = qc->next;
    q->length -= 1;

    free(qc);
    return c;
}

/* Print a representation of the queue 'q' to STDOUT*/
void queue_print(Queue *q) {
    int length = queue_length(q);
    QCell *c;

    printf("Queue (%d elements):\n", length);

    for (c = q->first; c != NULL; c = c->next) printf("    %c\n", c->value);
    printf("\n");
}

/* Deallocate the queue 'q'*/
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

/* Get the length of the queue 'q'*/
int queue_length(Queue *q) {
    return q->length;
}

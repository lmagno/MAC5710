#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _QCell QCell;
typedef struct _Queue Queue;

/* A single cell of the queue*/
struct _QCell {
    char value;
    struct _QCell *next;
};

/* The header of the queue*/
struct _Queue {
    int length;
    QCell *first;
    QCell *last;
};

Queue* queue_create();
void   queue_push(Queue *q, char c);
char queue_pop(Queue *q);
void   queue_free(Queue *q);
void   queue_print(Queue *q);
int    queue_length(Queue* q);

#endif

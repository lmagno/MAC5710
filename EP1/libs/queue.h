#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct _QCell QCell;
typedef struct _Queue Queue;

Queue* queue_create();
void   queue_push(Queue *q, Node *n);
Node*  queue_pop(Queue *q);
void   queue_free(Queue *q);
void   queue_print(Queue *q);
int    queue_length(Queue* q);

#endif

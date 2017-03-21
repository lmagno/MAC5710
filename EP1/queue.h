#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *q;
    int bottom;
    int top;
    int maxlen;
} Queue;

Queue* queue_create(int maxlen);
void   queue_push(Queue *q, int i);
int    queue_pop(Queue *q);
void   queue_free(Queue *q);
void   queue_print(Queue *q);

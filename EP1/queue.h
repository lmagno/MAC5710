#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *q;
    int bottom;
    int top;
    int maxlen;
} Queue;

Queue* qcreate(int maxlen);
void   qpush(Queue *q, int i);
int    qpop(Queue *q);
void   qfree(Queue *q);
void   qprint(Queue *q);

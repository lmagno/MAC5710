#include <stdio.h>
#include <stdlib.h>

typedef struct _QCell QCell;
typedef struct _Queue Queue;

Queue* qcreate();
void   qpush(Queue *q, int i);
int    qpop(Queue *q);
void   qfree(Queue *q);
void   qprint(Queue *q);
int    qlength(Queue* q);

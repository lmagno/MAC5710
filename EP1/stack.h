#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *s;
    int top;
    int maxlen;
} Stack;

Stack* screate(int maxlen);
void   spush(Stack *s, int i);
int    spop(Stack *s);
void   sfree(Stack *s);
void   sprint(Stack *s);

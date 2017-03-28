#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _SCell SCell;
typedef struct _Stack Stack;

Stack* screate();
void   spush(Stack *s, int i);
int    spop(Stack *s);
void   sfree(Stack *s);
void   sprint(Stack *s);
int    slength(Stack *s);

#endif

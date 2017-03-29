#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _SCell SCell;
typedef struct _Stack Stack;

Stack* stack_create();
void   stack_push(Stack *s, int i);
int    stack_pop(Stack *s);
void   stack_free(Stack *s);
void   stack_print(Stack *s);
int    stack_length(Stack *s);

#endif

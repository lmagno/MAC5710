#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *s;
    int top;
    int maxlen;
} Stack;

Stack* stack_create(int maxlen);
void stack_push(Stack *s, int i);
int stack_pop(Stack *s);
void stack_free(Stack *s);
void stack_print(Stack *s);

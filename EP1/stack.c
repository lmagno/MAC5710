#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* stack_create(int maxlen) {
    Stack *s;

    s = (Stack*)malloc(sizeof(Stack));
    s->maxlen = maxlen;
    s->top = 0;
    s->s = (int*)malloc(maxlen*sizeof(int));

    return s;
}

void stack_push(Stack *s, int i) {
    if (s->top == s->maxlen) {
        fprintf(stderr, "The stack is full! Cannot push into index %d.\n", s->maxlen);
        exit(EXIT_FAILURE);
    }
    s->s[s->top++] = i;
}

int stack_pop(Stack *s) {
    if (s->top == 0) {
        fprintf(stderr, "The stack is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    return s->s[--s->top];
}

void stack_print(Stack *s) {
    int i;

    printf("\n");
    for (i = 0; i < s->top; i++) printf("%4d", i);
    printf("\n");
    for (i = 0; i < s->top; i++) printf("%4d", s->s[i]);
    printf("\n");
}

void stack_free(Stack *s) {
    free(s->s);
    free(s);
}

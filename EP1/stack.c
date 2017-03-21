#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Allocate a stack of max length 'maxlen'
Stack* screate(int maxlen) {
    Stack *s;

    s = (Stack*)malloc(sizeof(Stack));
    s->maxlen = maxlen;
    s->top = 0;
    s->s = (int*)malloc(maxlen*sizeof(int));

    return s;
}

// Push value 'i' into the top of the stack 's',
// checking and exiting with failure if it's full
void spush(Stack *s, int i) {
    if (s->top == s->maxlen) {
        fprintf(stderr, "The stack is full! Cannot push into index %d.\n", s->maxlen);
        exit(EXIT_FAILURE);
    }
    s->s[s->top++] = i;
}

// Pop and return a value from the stack 's',
// checking and exiting with failure if it's empty
int spop(Stack *s) {
    if (s->top == 0) {
        fprintf(stderr, "The stack is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    return s->s[--s->top];
}

// Print a representation of the stack 's' to STDOUT
void sprint(Stack *s) {
    int i;

    printf("\n");
    for (i = 0; i < s->top; i++) printf("%4d", i);
    printf("\n");
    for (i = 0; i < s->top; i++) printf("%4d", s->s[i]);
    printf("\n");
}

// Deallocate stack 's'
void sfree(Stack *s) {
    free(s->s);
    free(s);
}

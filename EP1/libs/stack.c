#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* A single cell of the stack*/
struct _SCell {
    Node *value;
    struct _SCell *next;
};


/* The header of the queue*/
struct _Stack {
    int length;
    SCell *top;
};

/* Allocate an empty stack*/
Stack* stack_create() {
    Stack *s;

    s = (Stack*)malloc(sizeof(Stack));
    s->length = 0;
    s->top = NULL;

    return s;
}

/* Push value 'i' into the top of the stack 's'*/
void stack_push(Stack *s, Node *n) {
    SCell *c;

    /* Initialize a SCell with the value 'i'*/
    c = (SCell*)malloc(sizeof(SCell));
    c->value = n;

    /* Add it to the top of the stack*/
    c->next = s->top;
    s->top = c;

    s->length += 1;
}

/* Pop and return a value from the stack 's',*/
/* checking and exiting with failure if it's empty*/
Node* stack_pop(Stack *s) {
    SCell *c;
    Node *n;

    if (stack_length(s) == 0) {
        fprintf(stderr, "The stack is empty! Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    /* Pop the top cell*/
    c = s->top;

    /* Extract its value*/
    n = c->value;

    /* Set the second cell as the top*/
    s->top = c->next;
    s->length -= 1;

    free(c);
    return n;
}

/* Print a representation of the stack 's' to STDOUT*/
void stack_print(Stack *s) {
    SCell *c;
    Stack *inv; /* stack for inverting the order of the elements*/
    Node *n;

    if (stack_length(s) == 0) {
        printf("[]\n");
        return;
    }

    inv = stack_create();
    for (c = s->top; c != NULL; c = c->next) stack_push(inv, c->value);

    printf("[");
    n = stack_pop(inv);
    printf("(%d,%d)", n->i, n->j);
    while (stack_length(inv) > 0) {
        n = stack_pop(inv);
        printf(", (%d,%d)", n->i, n->j);
    }
    printf("]");
    printf("\n");

    stack_free(inv);
}

/* Deallocate stack 's'*/
void stack_free(Stack *s) {
    SCell *a, *b;

    a = s->top;
    while (a != NULL) {
        b = a->next;
        free(a);
        a = b;
    }

    free(s);
}

/* Get the length of the stack 's'*/
int stack_length(Stack *s) {
    return s->length;
}

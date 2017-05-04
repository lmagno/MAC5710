/*****************************************************/
/* Nome: Lucas Magno                                 */
/* Número USP: 7994983                               */
/* Exercício-Programa 2                              */
/*                                                   */
/* Executar o programa da forma:                     */
/*     $ ./EP2 dicionario.txt                        */
/*                                                   */
/* Resultados são impressos na stdout.               */
/*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bst.h"
#include "queue.h"

#define MAX 100

char* lower(char *l, char *s);
void count(uint8_t *letters, char *l);

int main(int argc, char const *argv[]) {
    int r;
    FILE *file;
    uint8_t letters[26];
    char s[MAX], l[MAX];
    Node **n, *m;
    BST *b;
    Key *k;
    Queue *q, *qmax;

    /* Create an empty BST */
    b = bst_create();

    /* Open input file */
    file = fopen(argv[1], "r");

    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Pointer to hold the node with the longest queue */
    qmax = NULL;
    while(1) {
        q = NULL;

        /* Read a word, lower it and count its letters */
        r = fscanf(file, "%s", s);
        if(ferror(file)) {
            fprintf(stderr, "ERROR: Couldn't read from file %s, fscanf returned %d.\n", argv[1], r);
            exit(EXIT_FAILURE);
        }
        lower(l, s);
        count(letters, l);

        /* Create a temporary key from the letters and look for it in the BST */
        k = key_create(letters);
        n = bst_search(b, k);
        free(k);

        /* If the key isn't on the BST, create a new node with
        this key and insert it */
        if(!(*n)) {
            m = node_create(letters);
            *n = m;
        } else {
            m = *n;
        }

        /* Add the original word 's' to the queue associated
        with the current key */
        q = node_get_queue(m);
        queue_push(q, s);

        /* Update qmax */
        if(!qmax)
            qmax = q;
        else if(q->length > qmax->length)
            qmax = q;

        /* Break loop if at the end of the file */
        if(feof(file)) break;
    }

    /* Present results */
    printf("Biggest set of anagrams (length = %d):\n", qmax->length);
    queue_print(qmax);

    /* Free allocations */
    bst_free(b);
    fclose(file);
    return 0;
}

/* Count the ocurrences of each letter in the lowered word 'l',
storing the values in the array 'letters' */
void count(uint8_t *letters, char *l) {
    int i, n = strlen(l);
    int a = 'a' - 'a';
    int z = 'z' - 'a';
    char c;

    for(i = a; i <= z; i++)
        letters[i] = 0;

    for(i = 0; i < n; i++) {
        c = l[i];
        letters[c - 'a'] += 1;
    }

}

/* Copy string 's' to string 'l', converting every letter to lowercase */
char* lower(char *l, char *s) {
    int i, n = strlen(s);
    char c;

    for(i = 0; i < n; i++) {
        c = s[i];
        if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
        l[i] = c;
    }
    l[i] = '\0';

    return l;
}

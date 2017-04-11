#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bst.h"
#include "queue.h"

#define MAX 100

char* lower(char *l, char *s);
void count(int8_t *cnt, char *l);

int main(int argc, char const *argv[]) {
    FILE *file;
    int8_t cnt[26];
    char s[MAX], l[MAX];
    Node *n;
    BST *b;
    Key *k;
    Queue *q, *qmax;

    b = bst_create();
    file = fopen(argv[1], "r");

    if(!file) {
        fprintf(stderr, "Couldn't open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    qmax = NULL;
    while(1) {
        q = NULL;
        fscanf(file, "%s", s);
        // printf("%s\n", s);
        lower(l, s);
        count(cnt, l);

        k = key_create(cnt);
        n = bst_search(b, k);
        free(k);
        if(!n) {
            n = node_create(cnt);
            bst_insert(b, n);
        }

        q = node_queue(n);
        queue_push(q, s);

        if(!qmax)
            qmax = q;
        else if(q->length > qmax->length)
            qmax = q;

        if(feof(file)) break;
    }
    // bst_traverse(b);
    printf("Biggest set of anagrams (length = %d):\n", qmax->length);
    queue_print(qmax);

    bst_free(b);
    fclose(file);
    return 0;
}

void count(int8_t *cnt, char *l) {
    int i, n = strlen(l);
    int a = 'a' - 'a';
    int z = 'z' - 'a';
    char c;

    for(i = a; i <= z; i++) cnt[i] = 0;

    for(i = 0; i < n; i++) {
        c = l[i];
        cnt[c - 'a'] += 1;
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

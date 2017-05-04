#include "gen.h"
#include "bst.h"
#include <time.h>

int main(int argc, char const *argv[]) {
    BST *b;
    char s[100];
    Queue *q, *qmax;
    uint8_t letters[26];
    int n, m, word, max, total, len;
    Node *node, **pnode;
    Key *k;
    FILE *file;

    /* No buffer for output */
    /*setbuf(stdout, NULL);*/

    /* Open output file */
    file = fopen(argv[1], "w");
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s for writing.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    word = 20;
    max = 20;
    n = 100;
    srand(time(NULL));

    b = bst_create();

    /* Create a random set of anagrams which will be the biggest */
    letters_random(letters, word);

    node = node_create(letters);
    bst_insert(b, node);

    qmax = node_get_queue(node);
    qmax = npermutations(letters, word, word, max);
    max = queue_length(qmax);


    printf("Biggest set of anagrams:\n");
    total = max;
    queue_print(qmax);

    while(queue_length(qmax) > 0) {
        queue_pop(qmax, s);
        fprintf(file, "%s\n", s);
    }

    while(total < n) {
        len = 1 + rand()%word;
        letters_random(letters, len);

        /* Create a temporary key from the letters and look for it in the BST */
        k = key_create(letters);
        pnode = bst_search(b, k);
        free(k);

        /* If the key is already on the BST, try again */
        if(*pnode != NULL)
            continue;

        /* If the key isn't on the BST, create a new node with
        this key and insert it */
        node = node_create(letters);
        *pnode = node;

        q = node_get_queue(node);

        do {
            m = min(n - total,rand()%max);
        } while (m == 0);

        q = npermutations(letters, len, len, m);
        total += queue_length(q);

        while(queue_length(q) > 0) {
            queue_pop(q, s);
            fprintf(file, "%s\n", s);
        }
    }

    fclose(file);
    bst_free(b);
    return 0;
}
int min(int a, int b) {
    return a < b ? a : b;
}

/* Generate all unique permutations of the letters indicated by 'letters'
in lexicographical order */
Queue* permutations(uint8_t letters[26], int wordlen, int partlen) {
    int i;
    char *s;
    uint8_t part[26];
    Queue *P, *Q;

    /* Allocate the queue that will hold the partial permutations */
    P = queue_create();

    /* Permutations of a single element is itself */
    if(partlen == 1) {
        s = (char*)malloc((wordlen+1)*sizeof(char));

        /* Fill the string with noise so that we don't get its length wrong */
        for(i = 0; i < wordlen; i++)
            s[i] = '*';

        /* Find the element present and put it at the end of the string */
        for(i = 0; i < 26; i++) {
            if(letters[i] > 0) {
                s[wordlen - 1] = 'a' + i;
                break;
            }
        }

        s[wordlen] = '\0';

        /* Put the word in the queue and return it */
        queue_push(P, s);
        return P;
    }

    /* Get a copy of the letters so that we can alter it safely */
    for(i = 0; i < 26; i++)
        part[i] = letters[i];

    /* For each (unique) letter present, get the concatenation of itself and each permutation of the remaining letters */
    for(i = 0; i < 26; i++) {
        if(letters[i] == 0) continue;

        /* Remaining letters and their permutations */
        part[i] -= 1;
        Q = permutations(part, wordlen, partlen-1);

        /* For each permutation, get the concatenation of the current letter
        and itself */
        while(queue_length(Q) > 0) {
            /* Get a permutation */
            s = (char*)malloc((wordlen+1)*sizeof(char));
            queue_pop(Q, s);

            /* Concatenation (write at appropriate position) */
            s[wordlen-partlen] = 'a' + i;
            queue_push(P, s);
        }

        /* Restore 'part' so that 'part == letters' */
        part[i] += 1;
        queue_free(Q);
    }

    return P;
}

/* Generate the 'n' first unique permutations of the letters indicated by 'letters'
in lexicographical order */
Queue* npermutations(uint8_t letters[26], int wordlen, int partlen, int n) {
    int i, np;
    char *s;
    uint8_t part[26];
    Queue *P, *Q;

    /* Allocate the queue that will hold the partial permutations */
    P = queue_create();

    /* Permutations of a single element is itself */
    if(partlen == 1) {
        s = (char*)malloc((wordlen+1)*sizeof(char));

        /* Fill the string with noise so that we don't get its length wrong */
        for(i = 0; i < wordlen; i++)
            s[i] = '*';

        /* Find the element present and put it at the end of the string */
        for(i = 0; i < 26; i++) {
            if(letters[i] > 0) {
                s[wordlen - 1] = 'a' + i;
                break;
            }
        }

        s[wordlen] = '\0';

        /* Put the word in the queue and return it */
        queue_push(P, s);
        return P;
    }

    /* Get a copy of the letters so that we can alter it safely */
    for(i = 0; i < 26; i++)
        part[i] = letters[i];


    /* For each (unique) letter present, get the concatenation of itself and each permutation of the remaining letters */
    np = 0; /* Number of permutations found so far */
    for(i = 0; i < 26; i++) {
        if(letters[i] == 0) continue;

        /* Remaining letters and their permutations */
        part[i] -= 1;
        Q = npermutations(part, wordlen, partlen-1, n);

        /* For each permutation, get the concatenation of the current letter
        and itself */
        while(queue_length(Q) > 0) {
            /* Get a permutation */
            s = (char*)malloc((wordlen+1)*sizeof(char));
            queue_pop(Q, s);

            /* Concatenation (write at appropriate position) */
            s[wordlen-partlen] = 'a' + i;
            queue_push(P, s);

            /* Stop if we already have enough permutations */
            if(++np == n) {
                queue_free(Q);
                return P;
            }

        }

        /* Restore 'part' so that 'part == letters' */
        part[i] += 1;

        queue_free(Q);
    }

    return P;
}

void word_random(char *word, uint8_t letters[26], int length) {
    int i, j, l, r;

    for(i = 0; i <= length; i++)
        word[i] = '\0';

    for(l = 0; l < 26; l++) {
        for(j = 0; j < letters[l]; j++) {
            do
                r = rand()%length;
            while(word[r]);

            word[r] = 'a' + l;
        }
    }

}

void letters_random(uint8_t letters[26], int length) {
    int i;

    /* Initialize array */
    for(i = 0; i < 26; i++)
        letters[i] = 0;

    /* Randomly distribute the letters */
    for(i = 0; i < length; i++)
        letters[rand()%26] += 1;
}

void letters_print(uint8_t letters[26]) {
    int i;

    for(i = 0; i < 26; i++) printf("%c ", 'a' + i);    printf("\n");
    for(i = 0; i < 26; i++) printf("%d ", letters[i]); printf("\n\n");
}

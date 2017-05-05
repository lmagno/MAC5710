/****************************************************************/
/* Nome: Lucas Magno                                            */
/* Número USP: 7994983                                          */
/* Exercício-Programa 2                                         */
/*                                                              */
/* Executar o programa da forma:                                */
/*     $ ./gen wordlen setlen dictlen output.txt                */
/* onde                                                         */
/*     wordlen: tamanho máximo das palavras                     */
/*      setlen: tamanho do maior conjunto de anagramas          */
/*     dictlen: número de palavras no dicionário                */
/*  output.txt: arquivo de saída onde será gravado o dicionário */
/*                                                              */
/* Resultados são impressos na stdout.                          */
/****************************************************************/
#include "gen.h"
#include "bst.h"
#include <time.h>

int main(int argc, char const *argv[]) {
    BST *b;
    char s[100];
    Queue *q, *qmax;
    uint8_t letters[26];
    int m, left, len;
    int wordlen, setlen, dictlen;
    Node *node, **pnode;
    Key *k;
    FILE *file;

    /* Check number of arguments */
    if(argc != 5) {
        fprintf(stderr, "ERROR: Wrong number of arguments. Expected %d, got %d.\n", 4, argc-1);
        exit(EXIT_FAILURE);
    }

    /* Open output file */
    file = fopen(argv[4], "w");
    if(!file) {
        fprintf(stderr, "ERROR: Couldn't open file %s for writing.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    wordlen = atoi(argv[1]);
     setlen = atoi(argv[2]);
    dictlen = atoi(argv[3]);
    srand(time(NULL));

    /* Use BST so we don't generate the same set of anagrams more than once */
    b = bst_create();

    /* Create a random set of anagrams which will be the biggest */
    letters_random(letters, wordlen);

    node = node_create(letters);
    bst_insert(b, node);

    qmax = node_get_queue(node);
    qmax = npermutations(letters, wordlen, wordlen, setlen);
    setlen = queue_length(qmax);


    /* Print it to stdout */
    printf("Biggest set of anagrams:\n");
    left = dictlen - setlen;
    queue_print(qmax);

    /* Print it to the output file */
    while(queue_length(qmax) > 0) {
        queue_pop(qmax, s);
        fprintf(file, "%s\n", s);
    }

    queue_free(qmax);

    /* Generate anagrams while there are still words left to fill the dictionary */
    while(left > 0) {
        len = 1 + rand()%wordlen;
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

        /* Get a random size 'm' for the next set of anagrams (1 ≤ m < max) */
        m = min(left, 1 + rand()%(setlen-1));

        /* Get at most 'm' permutations of 'letters' in lexicographical order */
        q = npermutations(letters, len, len, m);
        left -= queue_length(q);

        /* Write them to the output file */
        while(queue_length(q) > 0) {
            queue_pop(q, s);
            fprintf(file, "%s\n", s);
        }

        queue_free(q);
    }

    fclose(file);
    bst_free(b);
    return 0;
}

/* Simple function for the minimum of two integers */
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

    s = (char*)malloc((wordlen+1)*sizeof(char));

    /* Allocate the queue that will hold the partial permutations */
    P = queue_create();

    /* Permutations of a single element is itself */
    if(partlen == 1) {
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
            queue_pop(Q, s);

            /* Concatenation (write at appropriate position) */
            s[wordlen-partlen] = 'a' + i;
            queue_push(P, s);
        }

        /* Restore 'part' so that 'part == letters' */
        part[i] += 1;
        queue_free(Q);
    }

    free(s);
    return P;
}

/* Generate the 'n' first unique permutations of the letters indicated by 'letters'
in lexicographical order */
Queue* npermutations(uint8_t letters[26], int wordlen, int partlen, int n) {
    int i, np;
    char *s;
    uint8_t part[26];
    Queue *P, *Q;

    s = (char*)malloc((wordlen+1)*sizeof(char));
    /* Allocate the queue that will hold the partial permutations */
    P = queue_create();

    /* Permutations of a single element is itself */
    if(partlen == 1) {
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

    free(s);
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

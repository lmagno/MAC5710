#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _HeapNode {
    uint32_t key;
    uint8_t  value;
} HeapNode;

typedef struct _Heap {
    size_t max;
    size_t size;
    HeapNode *nodes;
} Heap;


Heap* heap_create(size_t max) {
    Heap *h;

    h = (Heap*)malloc(sizeof(Heap));
    h->max = max;
    h->size = 0;
    h->nodes = (HeapNode*)malloc((max+1)*sizeof(HeapNode));

    return h;
}

void heap_free(Heap *h) {
    free(h->nodes);
    free(h);
}

void heap_up(Heap *h, int i) {
    int j;
    HeapNode *T, aux;

    T = h->nodes;
    j = i/2;

    if(j >= 1) {
        if(T[i].key < T[j].key) {
            aux = T[i];
            T[i] = T[j];
            T[j] = aux;

            heap_up(h, j);
        }
    }
}

void heap_down(Heap *h, int i) {
    int j, n;
    HeapNode *T, aux;

    n = h->size;
    T = h->nodes;
    j = 2*i;

    if(j <= n) {
        /* Choose smallest child */
        if(j < n) {
            if(T[j+1].key < T[j].key)
                j++;
        }

        if(T[i].key > T[j].key) {
            aux = T[i];
            T[i] = T[j];
            T[j] = aux;

            heap_down(h, j);
        }
    }
}

void heap_push(Heap *h, HeapNode hn) {
    HeapNode *T;
    int n;

    if(h->size == h->max) {
        fprintf(stderr, "ERROR: Heap overflow!\n");
        exit(EXIT_FAILURE);
    }

    n = h->size;
    T = h->nodes;

    T[n+1] = hn;
    h->size++;

    heap_up(h, n+1);
}

HeapNode heap_pop(Heap *h) {
    HeapNode hn, *T;
    int n;
    if(h->size == 0) {
        fprintf(stderr, "ERROR: Heap underflow!\n");
        exit(EXIT_FAILURE);
    }

    n = h->size;
    T = h->nodes;

    hn = T[1];
    T[1] = T[n];
    h->size--;

    heap_down(h, 1);

    return hn;
}

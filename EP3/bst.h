#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node Node;
typedef struct BST BST;

int key_cmp(uint32_t k1, uint32_t k2);
Node* node_create(uint32_t key, uint8_t value);
BST* bst_create();
void bst_insert(BST *b, Node *n);
Node** bst_search(BST *b, uint32_t key);
void bst_traverse(BST *b);
void node_free(Node *n);
void bst_free(BST *b);

#endif

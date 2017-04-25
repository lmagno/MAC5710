#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

typedef struct Key Key;
typedef struct Value Value;
typedef struct Node Node;
typedef struct BST BST;

Key* key_create(uint8_t letters[26]);
Value* value_create();
int key_cmp(Key *k1, Key *k2);
Node* node_create(uint8_t letters[26]);
Queue* node_get_queue(Node *n);
BST* bst_create();
void bst_insert(BST *b, Node *n);
Node** bst_search(BST *b, Key *key);
void bst_traverse(BST *b);
void node_free(Node *n);
void bst_free(BST *b);

#endif

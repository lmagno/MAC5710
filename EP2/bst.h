#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Key Key;
typedef struct Value Value;
typedef struct Node Node;
typedef struct BST BST;

Key* key_create(int cnt[26]);
Value* value_create(int value);
int key_cmp(Key *k1, Key *k2);
Node* node_create(int cnt[26], int value);
BST* bst_create();
// Node* _insert(Node *root, Node *n);
void bst_insert(BST *b, Node *n);
// Node* _search(Node *n, Key *key);
Node* bst_search(BST *b, Key *key);
// void _traverse(Node *n, void (*callback)(Node *n));
void bst_traverse(BST *b);
void node_free(Node *n);
void bst_free(BST *b);

#endif

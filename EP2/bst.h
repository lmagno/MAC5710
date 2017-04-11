#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Key Key;
typedef struct Value Value;
typedef struct Node Node;
typedef struct BST BST;

Node* node_create(int key, int value);
BST* bst_create();
Node* _insert(Node *root, Node *n);
void bst_insert(BST *b, Node *n);
Node* _search(Node *n, Key *key);
Node* bst_search(BST *b, Key *key);
void _traverse(Node *n, void (*callback)(Node *n));
void bst_traverse(BST *b, void (*callback)(Node *n));
void node_free(Node *n);
void bst_free(BST *b);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _node {
    uint32_t key;
    bool isleaf;
    uint8_t value;
    struct _node *left;
    struct _node *right;
} node;

node* node_create(uint32_t key, uint8_t value, bool isleaf) {
    node *n;

    n = (node*)malloc(sizeof(node));
    n->key = key;
    n->isleaf = isleaf;
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

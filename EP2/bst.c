#include "bst.h"

/******************************************************************************/
/*                         Problem specific datatypes                         */
/******************************************************************************/
struct Key {
    int key;
};

struct Value {
    int value;
};

Key* key_create(int key) {
    Key *k;

    k = (Key*)malloc(sizeof(Key));
    k->key = key;

    return k;
}

Value* value_create(int value) {
    Value *v;

    v = (Value*)malloc(sizeof(Value));
    v->value = value;

    return v;
}

int key_cmp(Key *k1, Key *k2) {
    int cmp = k1->key - k2->key;

    if(cmp < 0)
        return -1;
    else if (cmp > 0)
        return 1;
    else
        return 0;
}

struct Node {
    Key *key;
    Value *value;

    Node *left, *right;
};

Node* node_create(int key, int value) {
    Node *n;

    n = (Node*)malloc(sizeof(Node));

    n->key   = key_create(key);
    n->value = value_create(value);
    n->left  = NULL;
    n->right = NULL;

    return n;
}

/******************************************************************************/
/*                                 Generic BST                                */
/******************************************************************************/

struct BST {
    Node *root;
};

BST* bst_create() {
    BST *b;

    b = (BST*)malloc(sizeof(BST));

    b->root = NULL;

    return b;
}

Node* _insert(Node *root, Node *n) {
    if(!root)
        root = n;
    else if(key_cmp(n->key, root->key) < 0)
        root->left  = _insert(root->left, n);
    else
        root->right = _insert(root->right, n);

    return root;
}

void bst_insert(BST *b, Node *n) {
    b->root = _insert(b->root, n);
}

Node* _search(Node *n, Key *key) {
    int cmp = key_cmp(key, n->key);

    if(!n || cmp == 0)
        return n;
    else if(cmp < 0)
        return _search(n->left, key);
    else
        return _search(n->right, key);
}
Node* bst_search(BST *b, Key *key) {
    return _search(b->root, key);
}

void _traverse(Node *n, void (*callback)(Node *n)) {
    if(!n) return;

    _traverse(n->left, callback);
    callback(n);
    _traverse(n->right, callback);
}

void bst_traverse(BST *b, void (*callback)(Node *n)) {
    _traverse(b->root, callback);
}

void node_free(Node *n) {
    if(!n) return;

    node_free(n->left);
    node_free(n->right);

    free(n->key);
    free(n->value);
    free(n);
}

void bst_free(BST *b) {
    node_free(b->root);
    free(b);
}

/******************************************************************************/
/*                                   Testing                                  */
/******************************************************************************/
void f(Node *n) {
    printf("(%d, %d) ", n->key->key, n->value->value);
}

int main(int argc, char const *argv[]) {
    BST *b;

    b = bst_create();
    bst_insert(b, node_create(5, 1));
    bst_insert(b, node_create(1, 2));
    bst_insert(b, node_create(4, 3));
    bst_insert(b, node_create(8, 4));
    bst_insert(b, node_create(3, 5));
    bst_insert(b, node_create(7, 6));
    bst_insert(b, node_create(9, 7));
    bst_insert(b, node_create(2, 8));
    bst_insert(b, node_create(6, 9));

    bst_traverse(b, &f);
    printf("\n");

    bst_free(b);
    return 0;
}

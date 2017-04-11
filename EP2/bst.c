#include "bst.h"

/******************************************************************************/
/*                         Problem specific datatypes                         */
/******************************************************************************/
struct Key {
    int cnt[26];
};

struct Value {
    Queue *queue;
};

Key* key_create(int cnt[26]) {
    int i;
    Key *k;

    k = (Key*)malloc(sizeof(Key));
    // k->cnt = (int*)malloc(26*sizeof(int));

    for(i = 0; i < 26; i++)
        k->cnt[i] = cnt[i];

    return k;
}

Value* value_create() {
    Value *v;

    v = (Value*)malloc(sizeof(Value));
    v->queue = queue_create();

    return v;
}

int key_cmp(Key *k1, Key *k2) {
    int i;

    for(i = 0; i < 26; i++) {
        if(k1->cnt[i] < k2->cnt[i])
            return -1;
        else if(k1->cnt[i] > k2->cnt[i])
            return 1;
    }

    return 0;
}

struct Node {
    Key *key;
    Value *value;

    Node *left, *right;
};

Node* node_create(int cnt[26]) {
    Node *n;

    n = (Node*)malloc(sizeof(Node));

    n->key   = key_create(cnt);
    n->value = value_create();
    n->left  = NULL;
    n->right = NULL;

    return n;
}

void node_free(Node *n) {
    if(!n) return;

    node_free(n->left);
    node_free(n->right);

    // free(n->key->cnt);
    free(n->key);
    queue_free(n->value->queue);
    free(n->value);
    free(n);
}

void callback(Node *n) {
    int i;
    for(i = 0; i < 26; i++)
        printf("%d ", n->key->cnt[i]);

    printf("| ");
    queue_print(n->value->queue);
}

Queue* node_queue(Node *n) {
    return n->value->queue;
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
    int cmp;

    if(!n)
        return n;

    cmp = key_cmp(key, n->key);
    if(cmp == 0)
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


void bst_traverse(BST *b) {
    _traverse(b->root, callback);
}

void bst_free(BST *b) {
    node_free(b->root);
    free(b);
}

/******************************************************************************/
/*                                   Testing                                  */
/******************************************************************************/
// void f(Node *n) {
//     int i;
//     for(i = 0; i < 26; i++)
//         printf("%d ", n->key->cnt[i]);
//
//     printf("| %d", n->value->value);
// }
//
// int main(int argc, char const *argv[]) {
//     BST *b;
//
//     b = bst_create();
//     bst_insert(b, node_create(5, 1));
//     bst_insert(b, node_create(1, 2));
//     bst_insert(b, node_create(4, 3));
//     bst_insert(b, node_create(8, 4));
//     bst_insert(b, node_create(3, 5));
//     bst_insert(b, node_create(7, 6));
//     bst_insert(b, node_create(9, 7));
//     bst_insert(b, node_create(2, 8));
//     bst_insert(b, node_create(6, 9));
//
//     bst_traverse(b, &f);
//     printf("\n");
//
//     bst_free(b);
//     return 0;
// }

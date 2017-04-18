#include "bst.h"

/* Internal functions */
Node** _search(Node **root, Key *key);
void _traverse(Node *n, void (*callback)(Node *n));


/******************************************************************************/
/*                         Problem specific datatypes                         */
/******************************************************************************/

/* Structs for key and value of a node' */
struct Key {
    int8_t letters[26];
};

struct Value {
    Queue *queue;
};

/* Allocate a key */
Key* key_create(int8_t letters[26]) {
    int i;
    Key *k;

    k = (Key*)malloc(sizeof(Key));

    for(i = 0; i < 26; i++)
        k->letters[i] = letters[i];

    return k;
}

/* Allocate a value */
Value* value_create() {
    Value *v;

    v = (Value*)malloc(sizeof(Value));
    v->queue = queue_create();

    return v;
}

/* Compare two keys, returning
    -1 if k1 < k2
     0 if k1 = k2
     1 if k1 > k2 */
int key_cmp(Key *k1, Key *k2) {
    int i;

    for(i = 0; i < 26; i++) {
        if(k1->letters[i] < k2->letters[i])
            return -1;
        else if(k1->letters[i] > k2->letters[i])
            return 1;
    }

    return 0;
}

/* Struct for a Node */
struct Node {
    Key *key;
    Value *value;

    Node *left, *right;
};

/* Allocate a node */
Node* node_create(int8_t letters[26]) {
    Node *n;

    n = (Node*)malloc(sizeof(Node));

    n->key   = key_create(letters);
    n->value = value_create();
    n->left  = NULL;
    n->right = NULL;

    return n;
}

/* Deallocate a node */
void node_free(Node *n) {
    if(!n) return;

    node_free(n->left);
    node_free(n->right);

    // free(n->key->letters);
    free(n->key);
    queue_free(n->value->queue);
    free(n->value);
    free(n);
}

/* Callback function used during a traversal of the BST */
void callback(Node *n) {
    int i;
    for(i = 0; i < 26; i++)
        printf("%d ", n->key->letters[i]);

    printf("| ");
    queue_print(n->value->queue);
}

/* Getter for queue (value) of a node */
Queue* node_get_queue(Node *n) {
    return n->value->queue;
}
/******************************************************************************/
/*                                 Generic BST                                */
/******************************************************************************/

/* Struct for a Binary Search Tree */
struct BST {
    Node *root;
};

/* Allocate a BST */
BST* bst_create() {
    BST *b;

    b = (BST*)malloc(sizeof(BST));

    b->root = NULL;

    return b;
}

/* Searches the BST 'b' for the key 'key'.
If 'b' is empty, returns a pointer to the root.
If it's not empty, recursively searches for a node with
the same key, starting with the root. If it finds it,
a pointer to this node is returned, otherwise a pointer
to where it should be is returned.*/
Node** bst_search(BST *b, Key *key) {
    if(!(b->root))
        return &(b->root);
    else
        return _search(&(b->root), key);
}

Node** _search(Node **root, Key *key) {
    int cmp;
    Node *n = *root;

    /* Compare the key with the current node's one */
    cmp = key_cmp(key, n->key);

    if(cmp == 0) {
        /* If the keys are equal, return a pointer
        to the current node */
        return root;
    } else if(cmp < 0) {
        /* If the key is smaller than the current node's,
        then look for it in the left subtree. If it is empty,
        return a pointer to its root, because that's where a node
        with this key should be inserted */
        if(!n->left)
            return &(n->left);
        else
            return _search(&(n->left), key);
    } else {
        /* If the key is bigger than the current node's,
        then look for it in the right subtree. If it is empty,
        return a pointer to its root, because that's where a node
        with this key should be inserted */
        if(!n->right)
            return &(n->right);
        else
            return _search(&(n->right), key);
    }
}

/* Insert a new node in the BST 'b' if there isn't a node
with the same key already */
void bst_insert(BST *b, Node *n) {
    Node **m;

    m = bst_search(b, n->key);
    if(!(*m))
        *m = n;
}

/* Recursively traverse the BST 'b' starting with the root,
calling the function 'callback' each node.*/
void bst_traverse(BST *b) {
    _traverse(b->root, callback);
}

void _traverse(Node *n, void (*callback)(Node *n)) {
    if(!n) return;

    _traverse(n->left, callback);
    callback(n);
    _traverse(n->right, callback);
}

/* Deallocate the BST 'b' */
void bst_free(BST *b) {
    node_free(b->root);
    free(b);
}

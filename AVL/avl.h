/*
    Binary Search Tree as described in the Introduction to Algorithms book
    by Cormen, Leiserson, Rivest and Stein
    https://www.amazon.com.br/Introduction-Algorithms-Thomas-H-Cormen/dp/0262033844
*/

#ifndef _AVL_H
#define _AVL_H

struct node {
    int key;
    struct node *left;
    struct node *right;
    struct node *p;  // parent
    int height;
};

struct tree {
    struct node *root;
    struct node *nil;
};

typedef struct node Node;
typedef struct tree Tree;

Node *create_node(int key);

void tree_init(Tree *t);
void tree_reset(Tree *t);
void tree_free(Tree *t);
void tree_insert(Tree *t, Node *n);
void tree_delete(Tree *t, Node *n);  // n is supposed to be a node of t

// Search
Node *tree_search(Tree t, Node *n, int key); // binary search
Node *iterative_tree_search(Tree t, Node *n, int key);  // iterative binary search
Node *tree_minimum(Tree t, Node *n);  // n isn't NULL
Node *tree_maximum(Tree t, Node *n);  // n isn't NULL
Node *tree_successor(Tree t, Node *n);    // n isn't NULL
Node *tree_predecessor(Tree t, Node *n);  // n isn't NULL

// Printing
void preorder_tree_walk(Node *n);
void inorder_tree_walk(Node *n);
void postorder_tree_walk(Node *n);

int is_avl_tree(Tree t);

#endif // _AVL_H
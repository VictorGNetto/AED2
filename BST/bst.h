/*
    Binary Search Tree as described in the Introduction to Algorithms book
    https://www.amazon.com.br/Introduction-Algorithms-Thomas-H-Cormen/dp/0262033844
*/

#ifndef _BST_H
#define _BST_H

struct node {
    int key;
    struct node *left;
    struct node *right;
    struct node *p;  // parent
};

struct tree {
    struct node *root;
};

typedef struct node Node;
typedef struct tree Tree;

Node *create_node(int key);

void tree_init(Tree *t);
void tree_insert(Tree *t, Node *n);
void tree_delete(Tree *t, Node *n);  // n is supposed to be a node of t

// Search
Node *tree_search(Node *n, int key); // binary search
Node *iterative_tree_search(Node *n, int key);  // iterative binary search
Node *tree_minimum(Node *n);  // n isn't NULL
Node *tree_maximum(Node *n);  // n isn't NULL
Node *tree_successor(Node *n);    // n isn't NULL
Node *tree_predecessor(Node *n);  // n isn't NULL

// Printing
void preorder_tree_walk(Node *n);
void inorder_tree_walk(Node *n);
void postorder_tree_walk(Node *n);


#endif // _BST_H
/*
    Binary Search Tree as described in the Introduction to Algorithms book
    https://www.amazon.com.br/Introduction-Algorithms-Thomas-H-Cormen/dp/0262033844
*/

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    if (n)
    {
        n->key = key;
        n->left = NULL;
        n->right = NULL;
        n->p = NULL;
    }

    return n;
}

void tree_init(Tree *t)
{
    t->root = NULL;
}

void tree_free(Tree *t)
{
    t->root = NULL;
}

void tree_insert(Tree *t, Node *n)
{
    Node *y = NULL;
    Node *x = t->root;

    while (x) // x != NULL
    {
        y = x;
        if (n->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    n->p = y;

    if (y == NULL)
        t->root = n;
    else if (n->key < y->key)
        y->left = n;
    else
        y->right = n;
}

/*
    Replaces the subtree u by v. Both u and v are expected to be
    subtrees of t.
*/
void _transplant(Tree *t, Node *u, Node *v)
{
    if (u->p == NULL)          // u isn't a child
        t->root = v;
    else if (u == u->p->left)  // u is the left child
        u->p->left = v;
    else                       // u is the right child
        u->p->right = v;
    
    if (v)
        v->p = u->p;
}

void tree_delete(Tree *t, Node *n)
{
    if (n->left == NULL)
        _transplant(t, n, n->right);
    else if (n->right == NULL)
        _transplant(t, n, n->left);
    else
    {
        Node *y = tree_minimum(n->right);
        if (y->p != n)  // y isn't a child of n
        {
            _transplant(t, y, y->right);
            y->right = n->right;
            y->right->p = y;
        }
        _transplant(t, n, y);
        y->left = n->left;
        y->left->p = y;
    }
}

Node *tree_search(Node *n, int key)
{
    // Works since C is short circuiting
    if (n == NULL || n->key == key)
        return n;
    
    if (key < n->key)
        return tree_search(n->left, key);
    else
        return tree_search(n->right, key);
}

Node *iterative_tree_search(Node *n, int key)
{
    while (n && n->key != key)
    {
        if (key < n->key)
            n = n->left;
        else
            n = n->right;
    }

    return n;    
}

Node *tree_minimum(Node *n)
{
    while (n->left)
    {
        n = n->left;
    }

    return n;
}

Node *tree_maximum(Node *n)
{
    while (n->right)
    {
        n = n->right;
    }

    return n;
}

/*
    If n has a right child: tree_minimum(n->right).
    if n hasn't a right chiled: first ancestor that isn't a right child.
*/
Node *tree_successor(Node *n)
{
    if (n->right)
        return tree_minimum(n->right);
    
    Node *y = n->p;
    while (y && n == y->right)
    {
        n = y;
        y = y->p;
    }

    return y;
}

/*
    If n has a left child: tree_maximum(n->left).
    if n hasn't a left chiled: first ancestor that isn't a left child.
*/
Node *tree_predecessor(Node *n)
{
    if (n->left)
        return tree_maximum(n->left);
    
    Node *y = n->p;
    while (y && n == y->left)
    {
        n = y;
        y = y->p;
    }

    return y;
}

void preorder_tree_walk(Node *n)
{
    if (n)
    {
        printf("%d", n->key);
        preorder_tree_walk(n->left);
        preorder_tree_walk(n->right);
    }
}

void inorder_tree_walk(Node *n)
{
    if (n)
    {
        inorder_tree_walk(n->left);
        printf("%d", n->key);
        inorder_tree_walk(n->right);
    }
}

void postorder_tree_walk(Node *n)
{
    if (n)
    {
        postorder_tree_walk(n->left);
        postorder_tree_walk(n->right);
        printf("%d", n->key);
    }
}
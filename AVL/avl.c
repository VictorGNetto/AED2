/*
    Binary Search Tree as described in the Introduction to Algorithms book
    by Cormen, Leiserson, Rivest and Stein
    https://www.amazon.com.br/Introduction-Algorithms-Thomas-H-Cormen/dp/0262033844
    
*/

#include <stdlib.h>
#include <stdio.h>

#include "avl.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

//  n->right is not NULL
Node *_left_rotate(Tree *t, Node *n)
{
    Node *y = n->right;
    n->right = y->left;
    if (y->left != t->nil)
        y->left->p = n;
    y->p = n->p;

    if (n->p == t->nil)
        t->root = y;
    else if (n == n->p->left)
        n->p->left = y;
    else
        n->p->right = y;
    
    y->left = n;
    n->p = y;

    n->height = max(n->left->height, n->right->height) + 1;
    y->height = max(y->left->height, y->right->height) + 1;

    return y;
}

//  n->left is not NULL
Node *_right_rotate(Tree *t, Node *n)
{
    Node *y = n->left;
    n->left = y->right;
    if (y->right != t->nil)
        y->right->p = n;
    y->p = n->p;

    if (n->p == t->nil)
        t->root = y;
    else if (n == n->p->right)
        n->p->right = y;
    else
        n->p->left = y;
    
    y->right = n;
    n->p = y;

    n->height = max(n->left->height, n->right->height) + 1;
    y->height = max(y->left->height, y->right->height) + 1;

    return y;
}

Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    if (n)
    {
        n->key = key;
    }

    return n;
}

void tree_init(Tree *t)
{
    t->nil = (Node *) malloc(sizeof(Node));
    if (t->nil)
    {
        t->nil->height = -1;
    }

    t->root = t->nil;
}

void tree_reset(Tree *t)
{
    t->root = t->nil;
}

void tree_free(Tree *t)
{
    if (t)
        free(t->nil);
}

int abs(int n)
{
    return n > 0 ? n : -n;
}

Node *_avl_property_fixup(Tree *t, Node *n)
{
    int balanceFactor = n->left->height - n->right->height;
    if (abs(balanceFactor) > 1)
    {
        if (balanceFactor > 0)  // unbalanced on the left
        {
            if (n->left->left->height >= n->left->right->height)
            {
                n = _right_rotate(t, n);
            }
            else
            {
                _left_rotate(t, n->left);
                n = _right_rotate(t, n);
            }
        }
        else  // unbalanced on the right
        {
            if (n->right->right->height >= n->right->left->height)
            {
                n = _left_rotate(t, n);
            }
            else
            {
                _right_rotate(t, n->right);
                n = _left_rotate(t, n);
            }
        }
        
    }

    return n;
}

void _avl_fixup(Tree *t, Node *n)
{
    while (n != t->nil)
    {
        n->height = max(n->left->height, n->right->height) + 1;
        n = _avl_property_fixup(t, n);
        n = n->p;
    }
}

void tree_insert(Tree *t, Node *n)
{
    Node *y = t->nil;
    Node *x = t->root;

    while (x != t->nil)
    {
        y = x;
        if (n->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    n->p = y;

    if (y == t->nil)
        t->root = n;
    else if (n->key < y->key)
        y->left = n;
    else
        y->right = n;
    
    n->left = t->nil;
    n->right = t->nil;
    n->height = 0;
    _avl_fixup(t, n->p);
}

/*
    Replaces the subtree u by v. Both u and v are expected to be
    subtrees of t.
*/
void _transplant(Tree *t, Node *u, Node *v)
{
    if (u->p == t->nil)          // u isn't a child
        t->root = v;
    else if (u == u->p->left)  // u is the left child
        u->p->left = v;
    else                       // u is the right child
        u->p->right = v;
    
    v->p = u->p;
}

/*
    case 1 - n's sibling w is red
    case 2 - n's sibling w is black and both of w's children are black
    case 3 - n's sibling w is black, w's left child is red and w's right child is black
    case 4 - n's sibling w is black and w's right child is red
*/
void _avl_delete_fixup(Tree *t, Node *n)
{
}

void tree_delete(Tree *t, Node *n)
{
    if (n == t->nil) return;
    
    Node *y, *x;
    if (n->left == t->nil)  // n->right is a leaf or a nil node
    {
        x = n->right;
        _transplant(t, n, n->right);
        _avl_fixup(t, n->p);
        return;
    }
    else if (n->right == t->nil)  // n->left is a leaf or a nil node
    {
        x = n->left;
        _transplant(t, n, n->left);
        _avl_fixup(t, n->p);
        return;
    }
    else
    {
        y = tree_minimum(*t, n->right);
        x = y->right;
        if (y->p == n)
            x->p = y;
        else  // y isn't a child of n
        {
            _transplant(t, y, y->right);
            y->right = n->right;
            y->right->p = y;
        }
        _transplant(t, n, y);
        y->left = n->left;
        y->left->p = y;

        _avl_fixup(t, tree_minimum(*t, y->right));
    }
}

Node *tree_search(Tree t, Node *n, int key)
{
    // Works since C is short circuiting
    if (n == t.nil || n->key == key)
        return n;
    
    if (key < n->key)
        return tree_search(t, n->left, key);
    else
        return tree_search(t, n->right, key);
}

Node *iterative_tree_search(Tree t, Node *n, int key)
{
    while (n != t.nil && n->key != key)
    {
        if (key < n->key)
            n = n->left;
        else
            n = n->right;
    }

    return n;
}

Node *tree_minimum(Tree t, Node *n)
{
    if (n == t.nil) return n;

    while (n->left != t.nil)
    {
        n = n->left;
    }

    return n;
}

Node *tree_maximum(Tree t, Node *n)
{
    if (n == t.nil) return n;

    while (n->right != t.nil)
    {
        n = n->right;
    }

    return n;
}

/*
    If n has a right child: tree_minimum(n->right).
    if n hasn't a right chiled: first ancestor that isn't a right child.
*/
Node *tree_successor(Tree t, Node *n)
{
    if (n->right != t.nil)
        return tree_minimum(t, n->right);
    
    Node *y = n->p;
    while (y != t.nil && n == y->right)
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
Node *tree_predecessor(Tree t, Node *n)
{
    if (n->left != t.nil)
        return tree_maximum(t, n->left);
    
    Node *y = n->p;
    while (y != t.nil && n == y->left)
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

int is_avl_tree(Tree t)
{
    if (t.root == t.nil) return 1;  // an empty tree is an AVL tree

    int balanceFactor;
    Node *n = tree_minimum(t, t.root);
    Node *nMax = tree_maximum(t, t.root);
    while (n != nMax)
    {
        balanceFactor = n->left->height - n->right->height;
        if (abs(balanceFactor) > 1)
            return 0;
        n = tree_successor(t, n);
    }

    balanceFactor = nMax->left->height - nMax->right->height;
    return abs(balanceFactor) <= 1;
}
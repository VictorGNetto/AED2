/*
    Binary Search Tree as described in the Introduction to Algorithms book
    by Cormen, Leiserson, Rivest and Stein
    https://www.amazon.com.br/Introduction-Algorithms-Thomas-H-Cormen/dp/0262033844
    
*/

#include <stdlib.h>
#include <stdio.h>

#include "redblack.h"

//  n->right is not NULL
void _left_rotate(Tree *t, Node *n)
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
}

//  n->left is not NULL
void _right_rotate(Tree *t, Node *n)
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
        t->nil->color = BLACK;
    }

    t->root = t->nil;
}

void tree_free(Tree *t)
{
    if (t)
        free(t->nil);
}

void _rb_insert_fixup(Tree *t, Node *n)
{
    while (n->p->color == RED)
    {
        if (n->p == n->p->p->left)  // n's parent is the left child
        {
            Node *y = n->p->p->right;  // n's uncle
            if (y->color == RED)
            {
                n->p->color = BLACK;   // case 1
                y->color = BLACK;      // case 1
                n->p->p->color = RED;  // case 1
                n = n->p->p;           // case 1
            }
            else
            {
                if (n == n->p->right)
                {
                    n = n->p;            // case 2
                    _left_rotate(t, n);  // case 2
                }
                n->p->color = BLACK;        // case 3
                n->p->p->color = RED;       // case 3
                _right_rotate(t, n->p->p);  // case 3
            }
        }
        else  // n's parent is the right child
        {
            Node *y = n->p->p->left;  // n's uncle
            if (y->color == RED)
            {
                n->p->color = BLACK;   // case 1
                y->color = BLACK;      // case 1
                n->p->p->color = RED;  // case 1
                n = n->p->p;           // case 1
            }
            else
            {
                if (n == n->p->left)
                {
                    n = n->p;             // case 2
                    _right_rotate(t, n);  // case 2
                }
                n->p->color = BLACK;        // case 3
                n->p->p->color = RED;       // case 3
                _left_rotate(t, n->p->p);   // case 3
            }
        }
    }

    t->root->color = BLACK;
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
    n->color = RED;
    _rb_insert_fixup(t, n);
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
void _rb_delete_fixup(Tree *t, Node *n)
{
    while (n != t->root && n->color == BLACK)
    {
        if (n == n->p->left)
        {
            Node *w = n->p->right;  // n's sibling
            if (w->color == RED)
            {
                w->color = BLACK;       // case 1
                n->p->color = RED;      // case 1
                _left_rotate(t, n->p);  // case 1
                w = n->p->right;        // case 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;  // case 2
                n = n->p;        // case 2
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color == BLACK;  // case 3
                    w->color = RED;           // case 3
                    _right_rotate(t, w);      // case 3
                    w = n->p->right;          // case 3
                }
                w->color = n->p->color;   // case 4
                n->p->color = BLACK;      // case 4
                w->right->color = BLACK;  // case 4
                _left_rotate(t, n->p);
                n = t->root;
            }
        }
        else
        {
            Node *w = n->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;        // case 1
                n->p->color = RED;       // case 1
                _right_rotate(t, n->p);  // case 1
                w = n->p->left;          // case 1
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;  // case 2
                n = n->p;        // case 2
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color == BLACK;  // case 3
                    w->color = RED;            // case 3
                    _left_rotate(t, w);        // case 3
                    w = n->p->left;            // case 3
                }
                w->color = n->p->color;   // case 4
                n->p->color = BLACK;      // case 4
                w->left->color = BLACK;   // case 4
                _right_rotate(t, n->p);
                n = t->root;
            }
        }
    }
    n->color = BLACK;
}

void tree_delete(Tree *t, Node *n)
{
    Node *y, *x;
    y = n;
    int yOriginalColor = y->color;
    if (n->left == t->nil)
    {
        x = n->right;
        _transplant(t, n, n->right);
    }
    else if (n->right == t->nil)
    {
        x = n->left;
        _transplant(t, n, n->left);
    }
    else
    {
        y = tree_minimum(*t, n->right);
        yOriginalColor = y->color;
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
        y->color = n->color;
    }

    if (yOriginalColor == BLACK)
        _rb_delete_fixup(t, x);
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

Node *tree_minimum(Tree t, Node *n)
{
    while (n->left != t.nil)
    {
        n = n->left;
    }

    return n;
}

Node *tree_maximum(Tree t, Node *n)
{
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
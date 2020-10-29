#include <stdio.h>

#include "../redblack.h"

void show_node_info(Tree tree, Node * node)
{
    printf("%d - ", node->key);

    if (node->p != tree.nil)
        printf("[Parent = %d]", node->p->key);
    else
        printf("[Parent = X]");

    if (node->left != tree.nil)
        printf("[Left = %d]", node->left->key);
    else
        printf("[Left = X]");

    if (node->right != tree.nil)
        printf("[Right = %d]", node->right->key);
    else
        printf("[Right = X]");
    
    if (node->color == RED)
        printf("[ RED ]");
    else
        printf("[BLACK]");
    
    printf("\n");
}

// traverse a tree using the successor function
void traverse(Tree tree, Node * node)
{
    if (node != tree.nil)
    {
        show_node_info(tree, node);
        traverse(tree, tree_successor(tree, node));
    }   
}

int main()
{
    Tree tree;
    tree_init(&tree);

    /*     
           4
        2     6
       1 3   5 7

       preorder  -> 4213657
       inorder   -> 1234567
       postorder -> 1325764
    */
    tree_insert(&tree, create_node(4));
    tree_insert(&tree, create_node(2));
    tree_insert(&tree, create_node(3));
    tree_insert(&tree, create_node(1));
    tree_insert(&tree, create_node(6));
    tree_insert(&tree, create_node(7));
    tree_insert(&tree, create_node(5));

    traverse(tree, tree_minimum(tree, tree.root));

    tree_delete(&tree, iterative_tree_search(tree.root, 4));
    traverse(tree, tree_minimum(tree, tree.root));

    return 0;
}
#include <stdio.h>

#include "../bst.h"

// traverse a tree using the successor function
void traverse(Node * node)
{
    if (node)
    {
        printf("%d - ", node->key);

        if (node->p)
            printf("[Parent = %d]", node->p->key);
        else
            printf("[Parent = X]");

        if (node->left)
            printf("[Left = %d]", node->left->key);
        else
            printf("[Left = X]");

        if (node->right)
            printf("[Right = %d]", node->right->key);
        else
            printf("[Right = X]");
        
        printf("\n");

        traverse(tree_successor(node));
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

    preorder_tree_walk(tree.root);
    printf("\n");
    inorder_tree_walk(tree.root);
    printf("\n");
    postorder_tree_walk(tree.root);
    printf("\n");

    tree_delete(&tree, iterative_tree_search(tree.root, 2));
    traverse(tree_minimum(tree.root));

    // printf("%p\n", tree_search(tree.root, 0));            // (nil)
    // printf("%p\n", iterative_tree_search(tree.root, 1));  // 0x???????????????
    // printf("%p\n", tree_search(tree.root, 2));            // 0x???????????????
    // printf("%p\n", iterative_tree_search(tree.root, 3));  // 0x???????????????
    // printf("%p\n", tree_search(tree.root, 4));            // 0x???????????????
    // printf("%p\n", iterative_tree_search(tree.root, 5));  // 0x???????????????
    // printf("%p\n", tree_search(tree.root, 6));            // 0x???????????????
    // printf("%p\n", iterative_tree_search(tree.root, 7));  // 0x???????????????
    // printf("%p\n", tree_search(tree.root, 8));            // (nil)
    // printf("%p\n", iterative_tree_search(tree.root, 9));  // (nil)

    // printf("Min = %d\n", tree_minimum(tree.root)->key);
    // printf("Max = %d\n", tree_maximum(tree.root)->key);

    // Node *node = iterative_tree_search(tree.root, 1);
    // printf("%p -> %d\n", node, node->key);  // 1
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 2
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 3
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 4
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 5
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 6
    // node = tree_successor(node);
    // printf("%p -> %d\n", node, node->key);  // 7
    // node = tree_successor(node);
    // printf("%p\n", node);

    // node = iterative_tree_search(tree.root, 7);
    // printf("%p -> %d\n", node, node->key);  // 7
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 6
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 5
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 4
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 3
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 2
    // node = tree_predecessor(node);
    // printf("%p -> %d\n", node, node->key);  // 1
    // node = tree_predecessor(node);
    // printf("%p\n", node);
    

    return 0;
}
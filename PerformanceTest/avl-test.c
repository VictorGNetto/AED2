/*
    Makes a performance test in as BST with 100, 1000, 10000,
    100000 and 1000000 random and semi-random numbers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../AVL/avl.h"

#define NUMBER_OF_KEYS 1000000

Node *nodes[NUMBER_OF_KEYS];
Node *searchedNodes[NUMBER_OF_KEYS];
int keys[NUMBER_OF_KEYS];
Tree tree;

int randint(int a, int b)
{
    int d = b > a ? b - a + 1: a - b + 1;
    int s = b > a ? a : b;

    return a + rand() % d;
}

void shuffle(int v[], int n)
{
    int aux, a;
    for (int i = 0; i < n; i++)
    {
        a = randint(i, n - 1);
        if (a != i)  // swap v[i] with v[a]
        {
            aux = v[i];
            v[i] = v[a];
            v[a] = aux;
        }
    }
}

void make_test(int n, const char *fileName, double *insertionTime, double *searchTime, double *deletionTime)
{
    int key;
    FILE *file = fopen(fileName, "r");

    // Read some keys but not insert them into the tree
    int start = randint(0, NUMBER_OF_KEYS - n);
    for (int i = 0; i < start; i++)
        fscanf(file, "%d", &key);
    
    // Read the next n keys and create the nodes
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &keys[i]);
        nodes[i] = create_node(keys[i]);
    }

    // Insertion time
    clock_t startClock = clock();
    for (int i = 0; i < n; i++)
    {
        tree_insert(&tree, nodes[i]);
    }
    *insertionTime = (1000000.0 * (clock() - startClock)) / CLOCKS_PER_SEC;

    // Search time
    shuffle(keys, n);
    startClock = clock();
    for (int i = 0; i < n/2; i++)
    {
        searchedNodes[i] = iterative_tree_search(tree, tree.root, keys[i]);
    }
    *searchTime = (1000000.0 * (clock() - startClock)) / CLOCKS_PER_SEC;
    
    // Deletion time
    startClock = clock();
    for (int i = 0; i < n/2; i++)
    {
        tree_delete(&tree, searchedNodes[i]);
    }
    *deletionTime = (1000000.0 * (clock() - startClock)) / CLOCKS_PER_SEC;

    // Release resources
    for (int i = 0; i < n; i++)
    {
        free(nodes[i]);
    }
    tree_reset(&tree);
    fclose(file);
}

int main()
{
    srand(time(NULL));
    tree_init(&tree);
    double insertionTime, searchTime, deletionTime; // microseconds
    double totalInsertionTime, totalSearchTime, totalDeletionTime;
    FILE *file = fopen("avl-results", "w");
    int numberOfKeys[] = { 100, 1000, 10000, 100000, 1000000 };

    for (int i = 0; i < 5; i++)
    {
        printf("Starting test %d\n", i);
        totalInsertionTime = totalSearchTime = totalDeletionTime = 0;
        fprintf(file, "%d Random Keys\n", numberOfKeys[i]);
        for (int j = 0; j < 30; j++)
        {
            printf("    Random %d\n", j);
            make_test(numberOfKeys[i], "random-data", &insertionTime, &searchTime, &deletionTime);
            totalInsertionTime += insertionTime / 30;
            totalSearchTime += searchTime / 30;
            totalDeletionTime += deletionTime / 30;
        }
        fprintf(file, "Insertion: %lf us\tSearch: %lf us\tDeletion: %lf us\n", insertionTime, searchTime, deletionTime);

        totalInsertionTime = totalSearchTime = totalDeletionTime = 0;
        fprintf(file, "%d Semi-Random Keys\n", numberOfKeys[i]);
        for (int j = 0; j < 30; j++)
        {
            printf("    Semi-Random %d\n", j);
            make_test(numberOfKeys[i], "semi-random-data", &insertionTime, &searchTime, &deletionTime);
            totalInsertionTime += insertionTime / 30;
            totalSearchTime += searchTime / 30;
            totalDeletionTime += deletionTime / 30;
        }
        fprintf(file, "Insertion: %lf us\tSearch: %lf us\tDeletion: %lf us\n", insertionTime, searchTime, deletionTime);
    }

    fclose(file);

    return 0;
}
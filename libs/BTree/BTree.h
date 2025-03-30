#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int num_keys;
    int is_leaf;
} BTreeNode;

BTreeNode *init_BTree();
BTreeNode *create_BTree_node(int t);
void free_BTree(BTreeNode *a);
BTreeNode *search_BTree(BTreeNode* x, int ch);
BTreeNode *insert_BTree(BTreeNode *T, int k, int t);
BTreeNode* remove_BTree(BTreeNode* arv, int k, int t);
void print_BTree(BTreeNode *a);

#endif //BTREE_H

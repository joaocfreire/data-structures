#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* init_tree();
TreeNode* create_tree_node(int root, TreeNode* left, TreeNode* right);
TreeNode* search_tree_node(TreeNode* root, int data);
void pre_order_traversal(TreeNode* root);
void post_order_traversal(TreeNode* root);
void in_order_traversal(TreeNode* root);
int height_tree(TreeNode* root);
int total_tree_node(TreeNode* root);
void print_tree(TreeNode* root, int tab);
void free_tree(TreeNode* root);

#endif //BINARYTREE_H
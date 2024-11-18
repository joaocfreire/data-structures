#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* initTree();
TreeNode* createTreeNode(int root, TreeNode* left, TreeNode* right);
TreeNode* searchTreeNode(TreeNode* root, int data);
void preOrderTraversal(TreeNode* root);
void postOrderTraversal(TreeNode* root);
void inOrderTraversal(TreeNode* root);
int heightTree(TreeNode *root);
int totalTreeNode(TreeNode* root);
void printTree(TreeNode* root, int tab);
void freeTree(TreeNode* root);

#endif //BINARYTREE_H
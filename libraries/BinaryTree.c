#include "headers/BinaryTree.h"

TreeNode* initTree() {
    return NULL;
}

TreeNode* createTreeNode(int root, TreeNode* left, TreeNode* right) {
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    newNode->data = root;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

TreeNode* searchTreeNode(TreeNode* root, int data) {
    if (root == NULL || root->data == data) return root;
    TreeNode* s = searchTreeNode(root->left, data);
    if (s != NULL) return s;
    return searchTreeNode(root->right, data);
}

void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int max(int x, int y) {
    if (x >= y) return x;
    return y;
}

int heightTree(TreeNode *root) {
    if (root == NULL) return 0;
    return max(heightTree(root->left), heightTree(root->right)) + 1;
}

void printTree(TreeNode* root, int tab) {
    for (int i = 0; i < tab; i++) {
        printf(".");
    }
    if (root != NULL) {
        printf("%d\n", root->data);
        printTree(root->left, tab + 2);
        printf("\n");
        printTree(root->right, tab + 2);
    } else printf("vazio");
}

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
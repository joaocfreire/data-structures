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

void preOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void inOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
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

int totalTreeNode(TreeNode* root) {
    if (root == NULL) return 0;
    return totalTreeNode(root->left) + totalTreeNode(root->right) + 1;
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
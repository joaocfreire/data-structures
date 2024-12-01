#include "headers/BinaryTree.h"

TreeNode* init_tree() {
    return NULL;
}

TreeNode* create_tree_node(int root, TreeNode* left, TreeNode* right) {
    TreeNode* new = (TreeNode*) malloc(sizeof(TreeNode));
    new->data = root;
    new->left = left;
    new->right = right;
    return new;
}

TreeNode* search_tree_node(TreeNode* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    TreeNode* s = search_tree_node(root->left, data);
    if (s != NULL)
        return s;

    return search_tree_node(root->right, data);
}

void pre_order_traversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

void post_order_traversal(TreeNode* root) {
    if (root != NULL) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf("%d ", root->data);
    }
}

void in_order_traversal(TreeNode* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%d ", root->data);
        in_order_traversal(root->right);
    }
}

int max(int x, int y) {
    if (x >= y)
        return x;
    return y;
}

int height_tree(TreeNode *root) {
    if (root == NULL)
        return 0;
    return max(height_tree(root->left), height_tree(root->right)) + 1;
}

int total_tree_node(TreeNode* root) {
    if (root == NULL)
        return 0;
    return total_tree_node(root->left) + total_tree_node(root->right) + 1;
}

void print_tree(TreeNode* root, int tab) {
    for (int i = 0; i < tab; i++)
        printf(".");
    if (root != NULL) {
        printf("%d\n", root->data);
        print_tree(root->left, tab + 2);
        printf("\n");
        print_tree(root->right, tab + 2);
    }
    else
        printf("null");
}

void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
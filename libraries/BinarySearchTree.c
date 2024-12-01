#include "headers/BinarySearchTree.h"

TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data)
        return root;
    if (root->data > data)
        return search(root->left, data);
    return search(root->right, data);
}

TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL)
        return create_tree_node(data, NULL, NULL);
    if (root->data > data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

TreeNode* delete(TreeNode* root, int data) {
    if (root == NULL)
        return root;
    if (root->data > data)
        root->left = delete(root->left, data);
    else if (root->data < data)
        root->right = delete(root->right, data);
    else {
        // Caso 1: nó é folha
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        TreeNode* aux = NULL;
        // Caso 2a: nó só possui um filho (direita)
        if (root->left == NULL) {
            aux = root;
            root = root->right;
            free(aux);
            return root;
        }
        // Caso 2b: nó só possui um filho (esquerda)
        if (root->right == NULL) {
            aux = root;
            root = root->left;
            free(aux);
            return root;
        }
        // Caso 3: nó possui dois filhos
        aux = root->left;
        while (aux->right != NULL)
            aux = aux->right;
        root->data = aux->data;
        root->left = delete(root->left, aux->data);
    }
    return root;
}
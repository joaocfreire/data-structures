#include <string.h>
#include <math.h>
#include "../libraries/headers/Stack.h"
#include "../libraries/headers/Queue.h"
#include "../libraries/headers/BinaryTree.h"

/* ------------------------------- LISTA 2 ---------------------------------- */

/* 1) Implemente um programa em C que leia uma árvore A e responda se A é:
 * a) estritamente binária (possui 0 ou 2 filhos);
 * b) binária completa (diferença de nível entre as folhas é no máximo 1) ;
 * c) zigue-zague (todos os nós internos possuem exatamente um filho vazio);
 * d) imprima todas as folhas de uma árvore. */

bool estritamente_binaria(TreeNode* root) {
    if (root == NULL)
        return true;
    if ((root->left == NULL && root->right == NULL) ||
        (root->left != NULL && root->right != NULL))
        return estritamente_binaria(root->left) && estritamente_binaria(root->right);
    return false;
}

bool aux_binaria_completa(TreeNode* root, int altura_da_arvore, int nivel_do_no) {
    // Caso base: árvore vazia, retorna true
    if (root == NULL)
        return true;

    // Se for nó interno, verifica os filhos a esquerda e a direita, atualizando o nível
    if (!(root->left == NULL && root->right == NULL))
        return aux_binaria_completa(root->left, altura_da_arvore, nivel_do_no+1) &&
            aux_binaria_completa(root->right, altura_da_arvore, nivel_do_no+1);

    // Se for nó folha verifica se o nó está no último ou penúltimo nível da árvore
    if (nivel_do_no == altura_da_arvore || nivel_do_no == altura_da_arvore - 1)
        return true;

    return false;
}

bool binaria_completa(TreeNode* root) {
    // Calcula a altura máxima da árvore
    int height = height_tree(root);
    // Chama a função auxiliar, passando a altura da árvore e o nível da raiz (1)
    return aux_binaria_completa(root, height, 1);
}

bool zique_zague(TreeNode* root) {
    if (root == NULL)
        return true;
    if (!(root->left != NULL && root->right != NULL))
        return zique_zague(root->left) && zique_zague(root->right);
    return false;
}

void imprime_folhas(TreeNode* root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL)
            printf("%d ", root->data);
        imprime_folhas(root->left);
        imprime_folhas(root->right);
    }
}

/* 2) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em profundidade utilizando pilhas. */

void busca_profundidade_com_pilha(TreeNode* root) {
    int x;
    TreeNode* aux = root;
    Stack* stack = create_stack();
    push(stack, aux->data);

    while (!stack_empty(stack)) {
        if (aux != NULL)
            aux = aux->left;
        else {
            x = top(stack);
            pop(stack);
            aux = search_tree_node(root, x);
            printf("%d ", aux->data);
            if (aux->right)
                push(stack, aux->right->data);
            if (aux->left)
                push(stack, aux->left->data);
        }
    }
    free_stack(stack);
}

/* 3) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em largura utilizando filas. */

void busca_largura_com_fila(TreeNode* root) {
    int x;
    TreeNode* aux = root;
    Queue* queue = create_queue();
    enqueue(queue, aux->data);

    while (!queue_empty(queue)) {
        if (aux != NULL)
            aux = aux->left;
        else {
            x = front(queue);
            dequeue(queue);
            aux = search_tree_node(root, x);
            printf("%d ", aux->data);
            if (aux->left)
                enqueue(queue, aux->left->data);
            if (aux->right)
                enqueue(queue, aux->right->data);
        }
    }

    free_queue(queue);
}

/* 4) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em pós-ordem utilizando pilhas. */

void busca_pos_ordem_com_pilha(TreeNode* root) {
    int x;
    TreeNode* curr = root;
    TreeNode* prev = NULL;
    Stack* stack = create_stack();

    while (!stack_empty(stack) || curr != NULL) {
        if (curr != NULL) {
            push(stack, curr->data);
            curr = curr->left;
        }
        else {
            x = top(stack);
            TreeNode* top_node = search_tree_node(root, x);
            if (top_node->right != NULL && top_node->right != prev)
                curr = top_node->right;
            else {
                printf("%d ", x);
                prev = top_node;
                pop(stack);
            }
        }
    }
    free_stack(stack);
}

/* 5) Faça um programa com busca em pós-ordem (recursivo) para apagar
 * todos os nós de uma árvore A dada. Refaça o algoritmo em pré-ordem. */

void libera_em_pos_ordem(TreeNode* root) {
    if (root != NULL) {
        libera_em_pos_ordem(root->left);
        libera_em_pos_ordem(root->right);
        free(root);
    }
}

void libera_em_pre_ordem(TreeNode* root) {
    if (root != NULL) {
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        free(root);
        libera_em_pre_ordem(left);
        libera_em_pre_ordem(right);
    }
}

/* 6) Escreva uma função que determine se uma árvore binária é cheia ou não. */

bool binaria_cheia(TreeNode* root) {
    if (root == NULL)
        return true;

    int height = height_tree(root);
    int n = total_tree_node(root);

    if (pow(2, height) - 1 == n)
        return true;

    return false;
}

/* 7) Escreva uma função que cria uma imagem espelho de uma árvore binária,
 * isto é, todos os filhos à esquerda tornam-se filhos à direita, e vice-versa. */

TreeNode* espelho(TreeNode* root) {
    if (root == NULL)
        return root;

    TreeNode* aux = root->left;
    root->left = root->right;
    root->right = aux;
    espelho(root->left);
    espelho(root->right);

    return root;
}

/* 8) Escreva uma função que retorna o maior nó de uma árvore binária. */

TreeNode* maior_no(TreeNode* root) {
    if (root == NULL)
        return NULL;

    TreeNode* maior_esquerda = maior_no(root->left);
    TreeNode* maior_direita = maior_no(root->right);
    TreeNode* maior = root;

    if (maior_esquerda != NULL && maior_esquerda->data > maior->data)
        maior = maior_esquerda;

    if (maior_direita != NULL && maior_direita->data > maior->data)
        maior = maior_direita;

    return maior;
}

/* 9) Escreva uma função que retire os nós pares de uma árvore binária. */

TreeNode* retira_pares(TreeNode* root) {
    // Caso Base: árvore vazia
    if (root == NULL)
        return root;

    root->left = retira_pares(root->left);
    root->right = retira_pares(root->right);

    // Verifica se o nó é par
    if (root->data % 2 == 0) {
        // Caso 1: nó folha
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // Caso 2: nó com um filho
        else if (root->left == NULL || root->right == NULL) {
            TreeNode* aux = root;
            root = (root->left != NULL) ? root->left : root->right;
            free(aux);
        }
        // Caso 3: nó com dois filhos
        else {
            TreeNode* substituto = root->right;
            TreeNode* pai_substituto = root;
            while (substituto->left) {
                pai_substituto = substituto;
                substituto = substituto->left;
            }
            root->data = substituto->data;
            if (pai_substituto->left == substituto)
                pai_substituto->left = substituto->right;
            else
                pai_substituto->right = substituto->right;
            free(substituto);
        }
    }
    return root;
}

/* Função que constrói uma árvore a partir de inputs do usuário */
TreeNode* build_tree() {
    int op, root, child;
    char pos;
    bool flag = true;

    printf("Digite a raiz da arvore:");
    scanf("%d", &root);
    TreeNode* tree = create_tree_node(root, NULL, NULL);

    do {
        printf("\n\n--------------- MENU ARVORE BINARIA ---------------\n\n");
        printf("1. Inserir elemento\n");
        printf("2. Imprimir arvore\n");
        printf("3. Sair\n\n");

        printf("Sua opcao:");
        scanf("%d", &op);
        printf("\n");

        switch (op) {
            case 1:
                printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posicao (e/d):");
                scanf("%d %d %c", &root, &child, &pos);
                TreeNode *r = search_tree_node(tree, root);
                if (r == NULL)
                    flag = false;
                else {
                    if (pos == 'e')
                        r->left = create_tree_node(child, NULL, NULL);
                    else
                        r->right = create_tree_node(child, NULL, NULL);
                    printf("\nNumero %d foi inserido na arvore\n", child);
                }
                break;
            case 2:
                printf("\n");
                print_tree(tree, 0);
                printf("\n");
                break;
            case 3:
                flag = false;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (flag);
    return tree;
}

/* Programa Principal */
int main2(){
    TreeNode* tree = build_tree();

    printf("\n");
    print_tree(tree, 0);
    printf("\n\n");

    bool s = estritamente_binaria(tree);
    if (s) printf("A arvore eh estritamente binaria\n");
    else printf("A arvore nao eh estritamente binaria\n");

    s = binaria_completa(tree);
    if (s) printf("A arvore eh binaria completa\n");
    else printf("A arvore nao eh binaria completa\n");

    s = zique_zague(tree);
    if (s) printf("A arvore eh zique-zague\n");
    else printf("A arvore nao eh zique-zague\n");

    s = binaria_cheia(tree);
    if (s) printf("A arvore eh binaria cheia\n\n");
    else printf("A arvore nao eh binaria cheia\n\n");

    printf("Folhas da arvore: ");
    imprime_folhas(tree);

    printf("\n\nBusca em Profundidade: ");
    busca_profundidade_com_pilha(tree);
    printf("\n\nBusca em Largura: ");
    busca_largura_com_fila(tree);
    printf("\n\nBusca em Pos-Ordem: ");
    busca_pos_ordem_com_pilha(tree);
    printf("\n\n");

    printf("Espelho da arvore:\n\n");
    tree = espelho(tree);
    print_tree(tree, 0);
    printf("\n\n");

    TreeNode* maior = maior_no(tree);
    if (maior != NULL) printf("Maior no da arvore: %d\n\n", maior->data);
    else printf("Arvore vazia\n\n");

    tree = retira_pares(tree);
    print_tree(tree, 0);
    printf("\n\n");

    //liberaEmPosOrdem(tree);
    //liberaEmPreOrdem(tree);

    free_tree(tree);

    return 0;
}
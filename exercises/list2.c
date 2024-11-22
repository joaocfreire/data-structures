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

bool estritamenteBinaria(TreeNode* root) {
    if (root == NULL)
        return true;
    if ((root->left == NULL && root->right == NULL) ||
        (root->left != NULL && root->right != NULL))
        return estritamenteBinaria(root->left) && estritamenteBinaria(root->right);
    return false;
}

bool auxBinariaCompleta(TreeNode* root, int alturaDaArvore, int nivelDoNo) {
    // Caso base: árvore vazia, retorna true
    if (root == NULL)
        return true;

    // Se for nó interno, verifica os filhos a esquerda e a direita, atualizando o nível
    if (!(root->left == NULL && root->right == NULL))
        return auxBinariaCompleta(root->left, alturaDaArvore, nivelDoNo+1) &&
            auxBinariaCompleta(root->right, alturaDaArvore, nivelDoNo+1);

    // Se for nó folha verifica se o nó está no último ou penúltimo nível da árvore
    if (nivelDoNo == alturaDaArvore || nivelDoNo == alturaDaArvore - 1)
        return true;

    return false;
}

bool binariaCompleta(TreeNode* root) {
    // Calcula a altura máxima da árvore
    int height = heightTree(root);
    // Chama a função auxiliar, passando a altura da árvore e o nível da raiz (1)
    return auxBinariaCompleta(root, height, 1);
}

bool ziqueZague(TreeNode* root) {
    if (root == NULL)
        return true;
    if (!(root->left != NULL && root->right != NULL))
        return ziqueZague(root->left) && ziqueZague(root->right);
    return false;
}

void imprimeFolhas(TreeNode* root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL)
            printf("%d ", root->data);
        imprimeFolhas(root->left);
        imprimeFolhas(root->right);
    }
}

/* 2) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em profundidade utilizando pilhas. */

void buscaProfundidadeComPilha(TreeNode* root) {
    int x;
    TreeNode* aux = root;
    Stack* stack = createStack();
    push(stack, aux->data);

    while (!stackEmpty(stack)) {
        if (aux != NULL)
            aux = aux->left;
        else {
            pop(stack, &x);
            aux = searchTreeNode(root, x);
            printf("%d ", aux->data);
            if (aux->right)
                push(stack, aux->right->data);
            if (aux->left)
                push(stack, aux->left->data);
        }
    }
    freeStack(stack);
}

/* 3) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em largura utilizando filas. */

void buscaLarguraComFila(TreeNode* root) {
    int x;
    TreeNode* aux = root;
    Queue* queue = createQueue();
    enqueue(queue, aux->data);

    while (!queueEmpty(queue)) {
        if (aux != NULL)
            aux = aux->left;
        else {
            dequeue(queue, &x);
            aux = searchTreeNode(root, x);
            printf("%d ", aux->data);
            if (aux->left)
                enqueue(queue, aux->left->data);
            if (aux->right)
                enqueue(queue, aux->right->data);
        }
    }

    freeQueue(queue);
}

/* 4) Dada uma árvore binária A, construa um programa (não recursivo) que faça
 * uma busca em pós-ordem utilizando pilhas. */

void buscaPosOrdemComPilha(TreeNode* root) {
    int x;
    TreeNode* curr = root;
    TreeNode* last = NULL;
    Stack* stack = createStack();

    while (!stackEmpty(stack) || curr != NULL) {
        if (curr != NULL) {
            push(stack, curr->data);
            curr = curr->left;
        }
        else {
            x = top(stack);
            TreeNode* topNode = searchTreeNode(root, x);
            if (topNode->right != NULL && topNode->right != last)
                curr = topNode->right;
            else {
                printf("%d ", x);
                last = topNode;
                pop(stack, &x);
            }
        }
    }
    freeStack(stack);
}

/* 5) Faça um programa com busca em pós-ordem (recursivo) para apagar
 * todos os nós de uma árvore A dada. Refaça o algoritmo em pré-ordem. */

void liberaEmPosOrdem(TreeNode* root) {
    if (root != NULL) {
        liberaEmPosOrdem(root->left);
        liberaEmPosOrdem(root->right);
        free(root);
    }
}

void liberaEmPreOrdem(TreeNode* root) {
    if (root != NULL) {
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        free(root);
        liberaEmPreOrdem(left);
        liberaEmPreOrdem(right);
    }
}

/* 6) Escreva uma função que determine se uma árvore binária é cheia ou não. */

bool binariaCheia(TreeNode* root) {
    if (root == NULL)
        return true;

    int height = heightTree(root);
    int n = totalTreeNode(root);

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

TreeNode* maiorNo(TreeNode* root) {
    if (root == NULL)
        return NULL;

    TreeNode* maiorEsquerda = maiorNo(root->left);
    TreeNode* maiorDireita = maiorNo(root->right);
    TreeNode* maior = root;

    if (maiorEsquerda != NULL && maiorEsquerda->data > maior->data)
        maior = maiorEsquerda;

    if (maiorDireita != NULL && maiorDireita->data > maior->data)
        maior = maiorDireita;

    return maior;
}

/* 9) Escreva uma função que retire os nós pares de uma árvore binária. */

TreeNode* retiraPares(TreeNode* root) {
    // Caso Base: árvore vazia
    if (root == NULL)
        return root;

    root->left = retiraPares(root->left);
    root->right = retiraPares(root->right);

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
            TreeNode* paiSubstituto = root;
            while (substituto->left) {
                paiSubstituto = substituto;
                substituto = substituto->left;
            }
            root->data = substituto->data;
            if (paiSubstituto->left == substituto)
                paiSubstituto->left = substituto->right;
            else
                paiSubstituto->right = substituto->right;
            free(substituto);
        }
    }
    return root;
}


/* Função que constrói uma árvore a partir de inputs do usuário */
TreeNode* buildTree() {
    int node, root;
    printf("Digite a raiz da arvore:");
    scanf("%d", &node);
    TreeNode *a = createTreeNode(node, NULL, NULL);
    char flag;

    do {
        char s1[2];
        printf("\nQuer continuar inserindo nos na arvore (s/n)?");
        scanf("%s", &flag);
        if (flag == 'n')
            break;

        printf("\nDigite o pai (que deve existir), o filho a ser inserido na arvore e a posicao (e/d):");
        scanf("%d %d %s", &root, &node, s1);
        TreeNode *s2 = searchTreeNode(a, root);
        if (s2 == NULL)
            break;

        if (strcmp(s1, "e") == 0)
            s2->left = createTreeNode(node, NULL, NULL);
        else
            s2->right = createTreeNode(node, NULL, NULL);

    } while(1);

    return a;
}

/* Programa Principal */
void main2(){
    TreeNode* tree = buildTree();

    printf("\n");
    printTree(tree, 0);
    printf("\n\n");

    bool s = estritamenteBinaria(tree);
    if (s) printf("A arvore eh estritamente binaria\n");
    else printf("A arvore nao eh estritamente binaria\n");

    s = binariaCompleta(tree);
    if (s) printf("A arvore eh binaria completa\n");
    else printf("A arvore nao eh binaria completa\n");

    s = ziqueZague(tree);
    if (s) printf("A arvore eh zique-zague\n");
    else printf("A arvore nao eh zique-zague\n");

    s = binariaCheia(tree);
    if (s) printf("A arvore eh binaria cheia\n\n");
    else printf("A arvore nao eh binaria cheia\n\n");

    printf("Folhas da arvore: ");
    imprimeFolhas(tree);

    printf("\n\nBusca em Profundidade: ");
    buscaProfundidadeComPilha(tree);
    printf("\n\nBusca em Largura: ");
    buscaLarguraComFila(tree);
    printf("\n\nBusca em Pos-Ordem: ");
    buscaPosOrdemComPilha(tree);
    printf("\n\n");

    printf("Espelho da arvore:\n\n");
    tree = espelho(tree);
    printTree(tree, 0);
    printf("\n\n");

    TreeNode* maior = maiorNo(tree);
    if (maior != NULL) printf("Maior no da arvore: %d\n\n", maior->data);
    else printf("Arvore vazia\n\n");

    tree = retiraPares(tree);
    printTree(tree, 0);
    printf("\n\n");

    //liberaEmPosOrdem(tree);
    //liberaEmPreOrdem(tree);

    freeTree(tree);
}
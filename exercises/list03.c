#include "../libraries/headers/Queue.h"
#include "../libraries/headers/BinarySearchTree.h"

/* ------------------------------- LISTA 3 ---------------------------------- */

/* 1) Faça um programa que leia uma ABB, um nó desta árvore
 * e retorne todos seus ancestrais em uma fila. */

Queue* auxAncestrais(TreeNode* root, Queue* queue, int data) {
    if (root != NULL) {
        if (root->data == data)
            return queue;

        enqueue(queue, root->data);

        if (root->data > data)
            queue = auxAncestrais(root->left, queue, data);

        else if (root->data < data)
            queue = auxAncestrais(root->right, queue, data);

        return queue;
    }

    freeQueue(queue);
    return NULL;
}

Queue* ancestrais(TreeNode* root, int data) {
    if (root == NULL)
        return NULL;

    Queue* queue = createQueue();
    queue = auxAncestrais(root, queue, data);
    return queue;
}

/* 2) Faça um programa que leia uma ABB, um nó desta árvore
 * e retorne todos seus sucessores em uma fila. */

Queue* auxSucessores(TreeNode* root, Queue* queue, int data) {
    if (root == NULL)
        return queue;

    if (root->data != data)
        enqueue(queue, root->data);

    queue = auxSucessores(root->left, queue, data);
    queue = auxSucessores(root->right, queue, data);
    return queue;
}

Queue* sucessores(TreeNode* root, int data) {
    if (root == NULL)
        return NULL;

    TreeNode* node = search(root, data);
    Queue* queue = createQueue();
    queue = auxSucessores(node, queue, data);
    return queue;
}

/* 3) Faça um programa que leia uma ABB (pelo teclado) e imprima todos os nós da
 * árvore dentro de uma faixa de valores [min, max] fornecida também pelo usuário. */

void printInRange(TreeNode* root, int min, int max) {
    if (root != NULL) {
        if (root->data >= min && root->data <= max)
            printf("%d ", root->data);
        if (root->data > min)
            printInRange(root->left, min, max);
        if (root->data < max)
            printInRange(root->right, min, max);
    }
}

/* 4) Faça um algoritmo que torne uma árvore o mais balanceada possível.
 * Crie um vetor ordenado com os nós da árvore utilizando busca em ordem simétrica
 * e reconstrua a árvore a partir dele. */

int* treeToVet(TreeNode* root, int* vet, int* pos) {
    if (root == NULL)
        return vet;
    vet = treeToVet(root->left, vet, pos);
    vet[(*pos)] = root->data;
    (*pos)++;
    vet = treeToVet(root->right, vet, pos);
    return vet;
}

TreeNode* auxBalanceamento(TreeNode* root, int* vet, int inicio, int fim) {
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        root = insert(root, vet[meio]);
        auxBalanceamento(root, vet, inicio, meio-1);
        auxBalanceamento(root, vet, meio+1, fim);
    }
    return root;
}

TreeNode* balanceamento(TreeNode* root) {
    int tot = totalTreeNode(root);
    int* vet = (int*) malloc(sizeof(int)*tot);
    int pos = 0;
    vet = treeToVet(root, vet, &pos);
    freeTree(root);
    root = initTree();
    root = auxBalanceamento(root, vet, 0, tot-1);
    free(vet);
    return root;
}


/* Menu que realiza as operações de inserção, remoção e impressão
 * de uma árvorea partir de inputs do usuário */

TreeNode* buildSearchTree(TreeNode* root) {
    bool flag = true;
    int op, num;
    do {
        printf("\n\n--------------- MENU ABB ---------------\n\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Imprimir arvore\n");
        printf("4. Sair\n\n");
        printf("Sua opcao:");
        scanf("%d", &op);
        printf("\n");
        switch (op) {
            case 1:
                printf("Digite um numero para inserir na arvore:");
                scanf("%d", &num);
                root = insert(root, num);
                printf("\nNumero %d foi inserido na arvore\n", num);
                break;
            case 2:
                printf("Digite um numero para remover da arvore:");
                scanf("%d", &num);
                root = delete(root, num);
                printf("\nNumero %d foi removido da arvore\n", num);
                break;
            case 3:
                printf("\n");
                printTree(root, 0);
                printf("\n");
                break;
            case 4:
                flag = false;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (flag);
    return root;
}

/* Programa Principal */
void main() {
    TreeNode* tree = initTree();
    tree = buildSearchTree(tree);

    printTree(tree, 0);
    printf("\n\n");

    int num;
    Queue* q;

    printf("Digite um no para verificar seus ancestrais:");
    scanf("%d", &num);
    q = ancestrais(tree, num);
    printf("\n");
    printQueue(q);
    printf("\n\n");
    freeQueue(q);

    printf("Digite um no para verificar seus sucessores:");
    scanf("%d", &num);
    q = sucessores(tree, num);
    printf("\n");
    printQueue(q);
    printf("\n\n");
    freeQueue(q);

    int min, max;
    printf("Digite um intervalo [min, max]:");
    scanf("%d %d", &min, &max);
    printf("\nOs nos nesse intervalo sao: ");
    printInRange(tree, min, max);
    printf("\n\n");

    printf("Balanceando a arvore:\n\n");
    tree = balanceamento(tree);
    printTree(tree, 0);
    printf("\n");

    freeTree(tree);
}

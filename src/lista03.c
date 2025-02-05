#include "../libs/Queue/Queue.h"
#include "../libs/BinarySearchTree/BinarySearchTree.h"

/* ------------------------------- LISTA 3 ---------------------------------- */

/*
 * 1) Faça um programa que leia uma ABB, um nó desta árvore
 * e retorne todos seus ancestrais em uma fila.
 */

Queue* aux_ancestrais(TreeNode* root, Queue* queue, int data) {
    if (root != NULL) {
        if (root->data == data)
            return queue;

        enqueue(queue, root->data);

        if (root->data > data)
            queue = aux_ancestrais(root->left, queue, data);

        else if (root->data < data)
            queue = aux_ancestrais(root->right, queue, data);

        return queue;
    }

    free_queue(queue);
    return NULL;
}

Queue* ancestrais(TreeNode* root, int data) {
    if (root == NULL)
        return NULL;

    Queue* queue = create_queue();
    queue = aux_ancestrais(root, queue, data);
    return queue;
}

/*
 * 2) Faça um programa que leia uma ABB, um nó desta árvore
 * e retorne todos seus sucessores em uma fila.
 */

Queue* aux_sucessores(TreeNode* root, Queue* queue, int data) {
    if (root == NULL)
        return queue;

    if (root->data != data)
        enqueue(queue, root->data);

    queue = aux_sucessores(root->left, queue, data);
    queue = aux_sucessores(root->right, queue, data);
    return queue;
}

Queue* sucessores(TreeNode* root, int data) {
    if (root == NULL)
        return NULL;

    TreeNode* node = search(root, data);
    Queue* queue = create_queue();
    queue = aux_sucessores(node, queue, data);
    return queue;
}

/*
 * 3) Faça um programa que leia uma ABB (pelo teclado) e imprima todos os nós da
 * árvore dentro de uma faixa de valores [min, max] fornecida também pelo usuário.
 */

void print_in_range(TreeNode* root, int min, int max) {
    if (root != NULL) {
        if (root->data >= min && root->data <= max)
            printf("%d ", root->data);
        if (root->data > min)
            print_in_range(root->left, min, max);
        if (root->data < max)
            print_in_range(root->right, min, max);
    }
}

/*
 * 4) Faça um algoritmo que torne uma árvore o mais balanceada possível.
 * Crie um vetor ordenado com os nós da árvore utilizando busca em ordem simétrica
 * e reconstrua a árvore a partir dele.
 */

int* tree_to_vet(TreeNode* root, int* vet, int* pos) {
    if (root == NULL)
        return vet;
    vet = tree_to_vet(root->left, vet, pos);
    vet[(*pos)] = root->data;
    (*pos)++;
    vet = tree_to_vet(root->right, vet, pos);
    return vet;
}

TreeNode* aux_balanceamento(TreeNode* root, int* vet, int inicio, int fim) {
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        root = insert(root, vet[meio]);
        aux_balanceamento(root, vet, inicio, meio-1);
        aux_balanceamento(root, vet, meio+1, fim);
    }
    return root;
}

TreeNode* balanceamento(TreeNode* root) {
    int tot = total_tree_node(root);
    int* vet = (int*) malloc(sizeof(int)*tot);
    int pos = 0;
    vet = tree_to_vet(root, vet, &pos);
    free_tree(root);
    root = init_tree();
    root = aux_balanceamento(root, vet, 0, tot-1);
    free(vet);
    return root;
}


/*
 * Menu que realiza as operações de inserção, remoção e impressão
 * de uma árvore a partir de inputs do usuário
 */

TreeNode* build_search_tree(TreeNode* root) {
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
                print_tree(root, 0);
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
int main() {
    TreeNode* tree = init_tree();
    tree = build_search_tree(tree);

    print_tree(tree, 0);
    printf("\n\n");

    int num;
    Queue* q;

    printf("Digite um no para verificar seus ancestrais:");
    scanf("%d", &num);
    q = ancestrais(tree, num);
    printf("\n");
    print_queue(q);
    printf("\n\n");
    free_queue(q);

    printf("Digite um no para verificar seus sucessores:");
    scanf("%d", &num);
    q = sucessores(tree, num);
    printf("\n");
    print_queue(q);
    printf("\n\n");
    free_queue(q);

    int min, max;
    printf("Digite um intervalo [min, max]:");
    scanf("%d %d", &min, &max);
    printf("\nOs nos nesse intervalo sao: ");
    print_in_range(tree, min, max);
    printf("\n\n");

    printf("Balanceando a arvore:\n\n");
    tree = balanceamento(tree);
    print_tree(tree, 0);
    printf("\n");

    free_tree(tree);

    return 0;
}

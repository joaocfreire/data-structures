#include "../libraries/headers/Stack.h"
#include "../libraries/headers/Queue.h"

/* ------------------------------- LISTA 1 ---------------------------------- */

/* 1) Implemente uma pilha dinâmica e faça um programa
 * de menu para testar suas operações */

// Pilha implementada em "Stack.h"

void menu_pilha() {
    Stack* stack = create_stack();
    int op, num;
    bool flag = true;

    while (flag) {

        printf("\n---------- MENU PILHA ----------\n");
        printf("1. Empilhar elemento\n");
        printf("2. Desempilhar elemento\n");
        printf("3. Consultar topo\n");
        printf("4. Imprimir a pilha\n");
        printf("5. Zerar a pilha\n");
        printf("6. Sair\n");

        printf("\nEscolha uma opcao:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("\nDigite um numero para empilhar:");
                scanf("%d", &num);
                push(stack, num);
                printf("\nNumero %d entrou na pilha!\n", stack->top->data);
                break;
            case 2:
                num = top(stack);
                pop(stack);
                if (num)
                    printf("\nNumero %d saiu da pilha\n", num);
                else
                    printf("\nPilha vazia!\n");
                break;
            case 3:
                num = top(stack);
                printf("\nTopo da pilha: %d\n", num);
                break;
            case 4:
                printf("\n");
                print_stack(stack);
                printf("\n");
                break;
            case 5:
                free_stack(stack);
                stack = create_stack();
                printf("\nPilha zerada!\n");
                break;
            case 6:
                flag = false;
                printf("\nAte logo...\n");
                break;
            default:
                printf("\nOpcao invalida\n");
        }
    }

    free_stack(stack);
}

/* 2) Implemente uma fila dinâmica e faça um programa
 * de menu para testar suas operações */

// Fila Implementada em "Queue.h"

void menu_fila() {
    Queue* queue = create_queue();
    int op, num;
    bool flag = true;

    while (flag) {

        printf("\n---------- MENU FILA ----------\n");
        printf("1. Enfileirar elemento\n");
        printf("2. Desenfileirar elemento\n");
        printf("3. Imprimir a fila\n");
        printf("4. Zerar a fila\n");
        printf("5. Sair\n");

        printf("\nEscolha uma opcao:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("\nDigite um numero para enfileirar:");
                scanf("%d", &num);
                enqueue(queue, num);
                printf("\nNumero %d entrou na fila!\n", queue->first->data);
                break;
            case 2:
                num = front(queue);
                dequeue(queue);
                if (num)
                    printf("\nNumero %d saiu da fila\n", num);
                else
                    printf("\nFila vazia!\n");
                break;
            case 3:
                printf("\n");
                print_queue(queue);
                printf("\n");
                break;
            case 4:
                free_queue(queue);
                queue = create_queue();
                printf("\nFila zerada!\n");
                break;
            case 5:
                flag = false;
                printf("\nAte logo...\n");
                break;
            default:
                printf("\nOpcao invalida\n");
        }
    }

    free_queue(queue);
}

/* Programa Principal */
int main1() {
    menu_pilha();
    menu_fila();
    return 0;
}
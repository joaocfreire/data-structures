#include <stdbool.h>
#include "../libs/Graph/Graph.h"

/* ------------------------------- LISTA 5-1 ---------------------------------- */

/*
 * 1) Descubra a quantidade de arestas de um grafo
 */

int edges(GraphNode* graph) {
    int count = 0;
    GraphNode* g = graph;

    while (g != NULL) {
        NeighborNode* n = g->neighbors;
        while (n != NULL) {
            count++;
            n = n->next;
        }
        g = g->next;
    }

    // return count;  // para grafos orientados
    return count / 2; // para grafos não orientados
}

/*
 * 2) Ache a quantidade de vértices de um grafo
 */

int vertices(GraphNode* graph) {
    int count = 0;
    GraphNode* g = graph;
    while (g != NULL) {
        count++;
        g = g->next;
    }
    return count;
}

/*
 * 3) Verificar se o grafo, passado como parâmetro de entrada,
 * possui todos os nós com grau igual ao parâmetro k
 */

bool test_k(GraphNode* graph, int k) {
    bool ext = true;
    GraphNode* g = graph;

    while (g != NULL && ext == true) {
        int count = 0;
        NeighborNode* n = g->neighbors;
        while (n != NULL) {
            count++;
            n = n->next;
        }
        if (count != k)
            ext = false;
        g = g->next;
    }

    return ext;
}

/*
 * 4) Testar se dois grafos são iguais
 */

bool equal_graphs(GraphNode* graph_x, GraphNode* graph_y) {
    GraphNode* x = graph_x;
    while (x != NULL) {
        GraphNode* v = search_vertex(graph_y, x->id);
        if (v == NULL)
            return false;
        NeighborNode* nx = x->neighbors;
        while (nx != NULL) {
            NeighborNode* n = search_edge(graph_y, x->id, nx->id);
            if (n == NULL)
                return false;
            nx = nx->next;
        }
        x = x->next;
    }
    return true;
}

/* Menu para construir o grafo a partir de inputs do usuário */
GraphNode* build_graph() {
    GraphNode* graph = init_graph();
    int op, id_x, id_y;
    bool flag = true;

    do {
        printf("\n------------------ MENU GRAFO  ------------------\n");
        printf("1. Adiconar vertice ao grafo\n");
        printf("2. Adicionar aresta ao grafo\n");
        printf("3. Remover vertice do grafo\n");
        printf("4. Remover aresta do grafo\n");
        printf("5. Imprimir grafo\n");
        printf("6. Sair\n\n");

        printf("Sua opcao:");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("\nDigite o id do vertice:");
                scanf("%d", &id_x);
                graph = add_vertex(graph, id_x);
                printf("\nVertice %d adiconado ao grafo!\n", id_x);
                break;
            case 2:
                printf("\nDigite o id do vertice x:");
                scanf("%d", &id_x);
                printf("\nDigite o id do vertice y:");
                scanf("%d", &id_y);
                add_edge(graph, id_x, id_y);
                printf("\nAresta (%d, %d) adicionada ao grafo!\n", id_x, id_y);
                break;
            case 3:
                printf("\nDigite o id do vertice:");
                scanf("%d", &id_x);
                graph = remove_vertex(graph, id_x);
                printf("\nVertice %d removido do grafo!\n", id_x);
                break;
            case 4:
                printf("\nDigite o id do vertice x:");
                scanf("%d", &id_x);
                printf("\nDigite o id do vertice y:");
                scanf("%d", &id_y);
                remove_edge(graph, id_x, id_y);
                printf("\nAresta (%d, %d) removida do grafo!\n", id_x, id_y);
                break;
            case 5:
                printf("\n\n");
                print_graph(graph);
                printf("\n\n");
                break;
            case 6:
                flag = false;
                break;
            default:
                printf("\n\nOpcao invalida!\n\n");
                break;
        }
    } while (flag);
    return graph;
}

/* Programa Principal */
int main() {
    GraphNode* graph_x = build_graph();

    int x = edges(graph_x);
    printf("O grafo tem %d arestas\n", x);

    x = vertices(graph_x);
    printf("O grafo tem %d vertices\n\n", x);

    int k;
    printf("Entre com um grau k:");
    scanf("%d", &k);
    bool asw = test_k(graph_x, k);
    if (asw)
        printf("Todos os vertice possuem grau igual a %d\n\n", k);
    else
        printf("Algum vertice nao possui grau igual a %d\n\n", k);

    printf("Entre com um novo grafo:\n\n");
    GraphNode* graph_y = build_graph();
    asw = equal_graphs(graph_x, graph_y);
    if (asw)
        printf("Os grafos sao iguais!\n\n");
    else
        printf("Os grafos sao diferentes!\n\n");

    free_graph(graph_x);
    free_graph(graph_y);

    return 0;
}
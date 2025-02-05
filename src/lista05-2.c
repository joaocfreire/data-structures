#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ------------------------------- LISTA 5-2 ---------------------------------- */

/*
 *  Implemente um grafo que representa seguidores no Instagram.
 *  Cada pessoa tem nome e idade (nome é o id do vértice).
 *  Uma aresta (v1, v2) significa que v1 segue v2 no Instagram.
 *  Depois, implemente funções em C para responder às seguintes questões:

 *  1) Quantas pessoas uma determinada pessoa segue?
 *  2) Quem são os seguidores de uma determinada pessoa?
 *  3) Quem é a pessoa com mais seguidores?
 *  4) Quais são as pessoas que só seguem pessoas mais velhas do que ela própria?
 */

/* Implementação do Grafo represenando seguidores do instagram */

typedef struct neighbor {
    char name[10];
    int age;
    struct neighbor* next;
} Neighbor;

typedef struct insta_graph {
    char name[10];
    int age;
    Neighbor* following;
    struct insta_graph* next;
} InstaGraph;

// Inicializa o grafo com NULL
InstaGraph* init_insta_graph() {
    return NULL;
}

// Busca para verificar se um usuário está no grafo
InstaGraph* search_user(InstaGraph* graph, char* name) {
    if (graph == NULL || strcmp(graph->name, name) == 0)
        return graph;
    return search_user(graph->next, name);
}

// Adicona um usuário ao grafo se ele já não estiver
InstaGraph* add_user(InstaGraph* graph, char* name, int age) {
    InstaGraph* new = search_user(graph, name);
    if (new != NULL)
        return graph;
    new = (InstaGraph*) malloc(sizeof(InstaGraph));
    strcpy(new->name, name);
    new->age = age;
    new->following = NULL;
    new->next = graph;
    return new;
}

// Cria o arco {x, y} se ambos existirem (x passa a seguir y)
void follow_user(InstaGraph* graph, char* name_x, char* name_y) {
    InstaGraph* x = search_user(graph, name_x);
    InstaGraph* y = search_user(graph, name_y);
    if (x != NULL && y != NULL) {
        Neighbor* new = (Neighbor*) malloc(sizeof(Neighbor));
        strcpy(new->name, name_y);
        new->age = y->age;
        new->next = x->following;
        x->following = new;
    }
}

// Imprime o grafo
void print_insta_graph(InstaGraph* graph) {
    if (graph != NULL) {
        printf("Usuario: %s\n", graph->name);
        Neighbor* aux = graph->following;
        printf("Segue: ");
        while (aux != NULL) {
            printf("%s ", aux->name);
            aux = aux->next;
        }
        printf("\n\n");
        print_insta_graph(graph->next);
    }
}

// Libera a lista de seguindo de um usuário
void free_follow(Neighbor* f) {
    if (f != NULL) {
        free_follow(f->next);
        free(f);
    }
}

// Libera o grafo
void free_insta_graph(InstaGraph* graph) {
    if (graph != NULL) {
        free_follow(graph->following);
        free_insta_graph(graph->next);
        free(graph);
    }
}


/* Questões do Instagram*/

int following(InstaGraph* graph, char* name) {
    InstaGraph* g = search_user(graph, name);
    if (g == NULL)
        return 0;

    int count = 0;
    Neighbor* aux = g->following;

    while (aux != NULL) {
        count++;
        aux = aux->next;
    }

    return count;
}

int followers(InstaGraph* graph, char* name, bool flag) {
    InstaGraph* g = search_user(graph, name);
    if (g == NULL)
        return 0;

    int count = 0;
    g = graph;

    if (flag)
        printf("Seguidores: ");
    while (g != NULL) {
        Neighbor *f = g->following;
        while (f != NULL && strcmp(f->name, name) != 0)
            f = f->next;
        if (f != NULL) {
            count++;
            if (flag)
                printf("%s ", g->name);
        }
        g = g->next;
    }
    if (flag)
        printf("\n");

    return count;
}

InstaGraph* most_popular(InstaGraph* graph) {
    if (graph == NULL)
        return NULL;

    int max = 0;
    InstaGraph* g = graph, *ext = NULL;
    while (g != NULL) {
        int temp = followers(g, g->name, false);
        if (temp > max) {
            max = temp;
            ext = g;
        }
        g = g->next;
    }

    return ext;
}

bool aux_follow_older(InstaGraph* graph) {
    if (graph == NULL)
        return false;

    Neighbor* f = graph->following;
    bool ext = true ? f != NULL : false;
    while (f != NULL && ext == true) {
        if (f->age < graph->age)
            ext = false;
        f = f->next;
    }

    return ext;
}

int follow_older(InstaGraph* graph, bool flag) {
    if (graph == NULL)
        return 0;

    int count = 0;
    InstaGraph* g = graph;

    printf("Usuarios que so seguem pessoas mais velhas: ");
    while (g != NULL) {
        bool aux = aux_follow_older(g);
        if (aux == true) {
            count++;
            if (flag == true)
                printf("%s ", g->name);
        }
        g = g->next;
    }
    printf("\n");

    return count;
}


/* Menu para construir o grafo a partir de inputs do usuário */
InstaGraph* build_insta_graph() {
    InstaGraph* graph = init_insta_graph();
    char name[10], name_x[10], name_y[10];
    int op, age;
    bool flag = true;

    do {
        printf("\n------------------ GRAFO INSTAGRAM ------------------\n");
        printf("1. Adiconar usuario ao grafo\n");
        printf("2. Adicionar aresta ao grafo (x vai seguir y)\n");
        printf("3. Imprimir grafo\n");
        printf("4. Sair\n\n");

        printf("Sua opcao:");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("\nDigite o nome do usuario que deseja adiconar:");
                scanf("%s", name);
                printf("\nDigite a idade do usuario que deseja adicionar:");
                scanf("%d", &age);
                graph = add_user(graph, name, age);
                printf("\nUsuario %s adiconado ao grafo!\n", name);
                break;
            case 2:
                printf("\nDigite o nome do usuario x:");
                scanf("%s", name_x);
                printf("\nDigite o nome do usuario y:");
                scanf("%s", name_y);
                follow_user(graph, name_x, name_y);
                printf("\n%s segue %s agora\n", name_x, name_y);
                break;
            case 3:
                printf("\n\n");
                print_insta_graph(graph);
                printf("\n\n");
                break;
            case 4:
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
    InstaGraph* graph = build_insta_graph();

    int ext;
    char n[10];

    printf("Digite um nome para saber quantas pessoas ele segue e quantos seguidores ele tem:");
    scanf("%s", n);

    ext = following(graph, n);
    printf("\nUsuario %s segue %d pessoas\n\n", n, ext);

    ext = followers(graph, n, true);
    printf("Usuario %s tem %d seguidores\n\n", n, ext);

    InstaGraph* g = most_popular(graph);
    printf("Usuario mais popular: %s\n\n", g->name);

    ext = follow_older(graph, true);
    printf("%d usuarios so seguem pessoas mais velhas que eles mesmos\n", ext);

    free_insta_graph(graph);

    return 0;
}

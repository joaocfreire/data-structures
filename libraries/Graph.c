#include "headers/Graph.h"

GraphNode* init_graph() {
    return NULL;
}

GraphNode* search_vertex(GraphNode* graph, int id) {
    if (graph == NULL || graph->id == id)
        return graph;
    return search_vertex(graph->next, id);
}

GraphNode* add_vertex(GraphNode* graph, int id) {
    GraphNode* new = search_vertex(graph, id);
    if (new == NULL) {
        new = (GraphNode*) malloc(sizeof(GraphNode));
        new->id = id;
        new->next = graph;
        new->neighbors = NULL;
        graph = new;
    }
    return graph;
}

GraphNode* remove_vertex(GraphNode* graph, int id) {
    GraphNode* curr = graph;
    GraphNode* prev = NULL;

    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        while (curr->neighbors != NULL)
            remove_edge(graph, id, curr->neighbors->id);
        if (prev == NULL)
            graph = graph->next;
        else
            prev->next = curr->next;
        free(curr);
    }

    return graph;
}

void remove_neighbors(GraphNode* graph, int id_y) {
    GraphNode* x = graph;
    while (x != NULL) {
        remove_edge_digraph(graph, x->id, id_y);
        x = x->next;
    }
}

GraphNode* remove_vertex_digraph(GraphNode* graph, int id) {
    GraphNode* curr = graph;
    GraphNode* prev = NULL;

    while (curr != NULL && curr->id != id){
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        while (curr->neighbors != NULL)
            remove_edge_digraph(graph, id, curr->neighbors->id);

        remove_neighbors(graph, id);

        if (prev == NULL)
            graph = graph->next;
        else
            prev->next = curr->next;

        free(curr);
    }

    return graph;
}

NeighborNode* search_edge(GraphNode* graph, int id_x, int id_y) {
    GraphNode* x = search_vertex(graph, id_x);
    GraphNode* y = search_vertex(graph, id_y);
    NeighborNode* ext = NULL;

    if (x != NULL && y != NULL) {
        ext = x->neighbors;
        while (ext != NULL && ext->id != id_y)
            ext = ext->next;
    }
    return ext;
}

void aux_add_edge(GraphNode* graph, int id_x, int id_y) {
    GraphNode* x = search_vertex(graph, id_x);
    NeighborNode* new = (NeighborNode*) malloc(sizeof(NeighborNode));
    new->id = id_y;
    new->next = x->neighbors;
    x->neighbors = new;
}

void add_edge(GraphNode* graph, int id_x, int id_y) {
    NeighborNode* edge = search_edge(graph, id_x, id_y);
    if (edge == NULL) {
        aux_add_edge(graph, id_x, id_y);
        aux_add_edge(graph, id_y, id_x);
    }
}

void add_edge_digraph(GraphNode* graph, int id_x, int id_y) {
    NeighborNode* edge = search_edge(graph, id_x, id_y);
    if (edge == NULL)
        aux_add_edge(graph, id_x, id_y);
}

void aux_remove_edge(GraphNode* graph, int id_x, int id_y) {
    GraphNode* x = search_vertex(graph, id_x);

    if (x != NULL) {
        NeighborNode* prev = NULL;
        NeighborNode* curr = x->neighbors;

        while (curr != NULL && curr->id != id_y) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != NULL) {
            if (prev == NULL)
                x->neighbors = curr->next;
            else
                prev->next = curr->next;
        }

        free(curr);
    }
}

void remove_edge(GraphNode* graph, int id_x, int id_y) {
    NeighborNode* edge = search_edge(graph, id_x, id_y);
    if (edge != NULL) {
        aux_remove_edge(graph, id_x, id_y);
        aux_remove_edge(graph, id_y, id_x);
    }
}

void remove_edge_digraph(GraphNode* graph, int id_x, int id_y) {
    NeighborNode* edgde = search_edge(graph, id_x, id_y);
    if (edgde != NULL)
        aux_remove_edge(graph, id_x, id_y);
}

void print_graph(GraphNode* graph) {
    GraphNode* aux = graph;
    while (aux != NULL) {
        printf("Vertice %d\n", aux->id);
        printf("Vizinhos --> ");
        NeighborNode* n = aux->neighbors;

        if (aux->neighbors == NULL)
            printf("Vertice isolado");

        while (n != NULL) {
            printf("%d ", n->id);
            n = n->next;
        }

        printf("\n\n");
        aux = aux->next;
    }
}

void free_neighbors(NeighborNode* n) {
    if (n != NULL) {
        free_neighbors(n->next);
        free(n);
    }
}

void free_graph(GraphNode* graph) {
    if (graph != NULL) {
        free_neighbors(graph->neighbors);
        free_graph(graph->next);
        free(graph);
    }
}
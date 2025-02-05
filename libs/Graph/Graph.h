#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct neighbor_node {
    int id;
    struct neighbor_node* next;
} NeighborNode;

typedef struct graph_node {
    int id;
    NeighborNode* neighbors;
    struct graph_node* next;
} GraphNode;

GraphNode* init_graph();
GraphNode* search_vertex(GraphNode* graph, int id);
GraphNode* add_vertex(GraphNode* graph, int id);
GraphNode* remove_vertex(GraphNode* graph, int id);
GraphNode* remove_vertex_digraph(GraphNode* graph, int id);
NeighborNode* search_edge(GraphNode* graph, int id_x, int id_y);
void add_edge(GraphNode* graph, int id_x, int id_y);
void add_edge_digraph(GraphNode* graph, int id_x, int id_y);
void remove_edge(GraphNode* graph, int id_x, int id_y);
void remove_edge_digraph(GraphNode* graph, int id_x, int id_y);
void print_graph(GraphNode* graph);
void free_graph(GraphNode* graph);

#endif //GRAPH_H

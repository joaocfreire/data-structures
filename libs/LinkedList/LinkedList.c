#include "LinkedList.h"

Node* init_list() {
    return NULL;
}

Node* insert_front(Node* list, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = list;
    return new;
}

Node* insert_back(Node* list, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    if (list == NULL) // lista vazia
        list = new;
    else {
        if (list->next == NULL) // fim da lista
            list->next = new;
        else
            insert_back(list->next, data);
    }
    return list;
}

Node* search_in_list(Node* list, int data) {
    if (list == NULL || list->data == data)
        return list;
    return search_in_list(list->next, data);
}

Node* remove_from_list(Node* list, int data) {
    if (list == NULL)
        return list;
    if (list->data == data) {
        Node* aux = list;
        list = list->next;
        free(aux);
    }
    else
        list->next = remove_from_list(list->next, data);
    return  list;
}

void free_list(Node* list) {
    if (list) {
        free_list(list->next);
        free(list);
    }
}

void print_list(Node* list) {
    if (list) {
        printf("%d", list->data);
        if (list->next) {
            printf(" -> ");
            print_list(list->next);
        }
    }
}
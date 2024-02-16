#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

linked_list* linked_list_create() {
    linked_list* list = (linked_list*)malloc(sizeof(list));
    list->tail = NULL;
    return list;
}

void linked_list_destroy(linked_list** list) {
    node* current = (*list)->tail;
    while (current != NULL) {
        node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}

void linked_list_add(linked_list* list, void* data, int data_size, Type type) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->data_size = data_size;
    new_node->type = type;
    new_node->next = list->tail;
    list->tail = new_node;
}

void linked_list_remove(linked_list* list) {
    if (list == NULL) {
        return;
    }

    node* current = list->tail;
    if (current == NULL) {
        return;
    }

    list->tail = current->next;
    free(current->data);
    free(current);
}

void linked_list_print(linked_list* list) {
    node* current = list->tail;
    while (current != NULL) {
        switch (current->type) {
            case INT_TYPE:
                printf("%d\n", *((int*)current->data));
                break;
            case FLOAT_TYPE:
                printf("%f\n", *((float*)current->data));
                break;
            case DOUBLE_TYPE:
                printf("%lf\n", *((double*)current->data));
                break;
            case CHAR_TYPE:
                printf("%c\n", *(char*)current->data);
                break;
            case STRING_TYPE:
                printf("%s\n", (char*)current->data);
                break;
            case POINTER_TYPE:
                printf("%p\n", current->data);
                break;
            default:
                printf("Non standard type\n");
                break;
        }
        current = current->next;
    }
}

void* get_tail_data(linked_list* list) {
    return list->tail->data;
}
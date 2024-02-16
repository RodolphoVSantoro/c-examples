#ifndef LINKED_LIST_H
#define LINKED_LIST_H

enum Type {
    INT_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    CHAR_TYPE,
    STRING_TYPE,
    POINTER_TYPE,
    NON_STANDARD_TYPE
};
typedef enum Type Type;

struct node {
    void* data;
    int data_size;
    Type type;
    struct node* next;
};

typedef struct node node;

struct linked_list {
    node* tail;
};

typedef struct linked_list linked_list;

linked_list* linked_list_create();

void linked_list_destroy(linked_list** list);

void linked_list_add(linked_list* list, void* data, int data_size, Type type);

void linked_list_remove(linked_list* list);

void linked_list_print(linked_list* list);

void* get_tail_data(linked_list* list);
#endif
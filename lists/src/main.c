#include <stdio.h>

#include "linked_list.h"

int main() {
    linked_list* list = linked_list_create();

    int a = 1;
    linked_list_add(list, &a, sizeof(int), INT_TYPE);

    int b = 2;
    linked_list_add(list, &b, sizeof(int), INT_TYPE);

    char c = 'c';
    linked_list_add(list, &c, sizeof(char), CHAR_TYPE);

    double d = 3.14;
    linked_list_add(list, &d, sizeof(double), DOUBLE_TYPE);

    float e = 2.71;
    linked_list_add(list, &e, sizeof(float), FLOAT_TYPE);

    linked_list_print(list);

    int array[] = {20, 2, 3, 4, 5};
    linked_list_add(list, array, sizeof(array), NON_STANDARD_TYPE);

    int* array2 = (int*)get_tail_data(list);

    for (int i = 0; i < 5; i++) {
        printf("%d\n", array2[i]);
    }

    linked_list_destroy(&list);

    return 0;
}

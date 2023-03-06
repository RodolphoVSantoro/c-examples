#include <stdio.h>
#include <stdlib.h>

struct Point3D {
    int x;
    int y;
    int z;
};

int main() {
    int *number_heap_array = malloc(sizeof(int) * 5);
    free(number_heap_array);

    // read from user input
    int n;
    scanf("%d", &n);
    struct Point3D *point_heap_array = malloc(sizeof(struct Point3D) * n);
    free(point_heap_array);

    struct Point3D *may_change_type_heap_array = malloc(sizeof(*may_change_type_heap_array) * n);
    free(may_change_type_heap_array);

    return 0;
}

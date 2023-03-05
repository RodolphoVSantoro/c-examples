#include <stdio.h>
#include <stdlib.h>

int main() {
    int magic_number = 42;
    int *magic_location = &magic_number;

    printf("value of magic_number = %d\n", magic_number);
    printf("value of magic_number = value of *magic_location = %d\n", *magic_location);
    printf("location of magic_number = &magic_number = magic_location = %p = %p\n", (void *)magic_location, (void *)&magic_number);
    return 0;
}
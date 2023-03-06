#include <stdio.h>
#include <stdlib.h>

int main() {
    int magic_number = 42;
    int *magic_number_location = &magic_number;

    char magic_char = 42;
    char *magic_char_location = &magic_char;

    void *magic_location = NULL;

    printf("sizeof(int) = %lld\n\n", sizeof(int));
    printf("sizeof(magic_number) = sizeof(int) = %lld\n\n", sizeof(magic_number));
    printf("sizeof(char) = %lld\n\n", sizeof(char));
    printf("sizeof(magic_char) = sizeof(char) = %lld\n\n", sizeof(magic_char));
    printf("sizeof(void *) = %lld\n\n", sizeof(void *));
    printf("sizeof(magic_location) = sizeof(void *) = %lld\n\n", sizeof(magic_location));
    printf("sizeof(magic_number_location) = sizeof(void *) = %lld\n\n", sizeof(magic_number_location));
    printf("sizeof(magic_char_location) = sizeof(void *) = %lld\n\n", sizeof(magic_char_location));

    // error: invalid application of 'sizeof' to a void type [-Werror=pointer-arith]
    // printf("sizeof(*magic_location) = %lld\n\n", sizeof(*magic_location));
    // error: invalid application of 'sizeof' to a void type [-Werror=pointer-arith]
    // printf("sizeof(void) = %lld\n\n", sizeof(void));

    return 0;
}
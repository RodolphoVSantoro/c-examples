#include <stdio.h>
#include <stdlib.h>

int main() {
    void *magic_location = NULL;  // NULL == 0x0
    // Equivalent to, but worse:
    // void *magic_location = 0x0;  // NULL == 0x0

    int magic_number = 1024 + 42;  // = 1066
    char magic_char = 42;

    int *magic_number_location = &magic_number;
    char *magic_char_location = &magic_char;

    printf("Start of memory: %p\n\n", magic_location);

    printf("value magic_number_location references = %d\n", *magic_number_location);
    printf("value magic_char_location references = %c\n\n", *magic_char_location);

    magic_location = (void *)magic_number_location;
    printf("value magic_location references = %d\n", *((int *)magic_location));
    magic_location = (void *)magic_char_location;
    printf("value magic_location references = %c\n\n", *((char *)magic_location));

    // error: dereferencing 'void *' pointer
    // printf("value magic_location references = %d\n", *magic_location);

    // May be a silent error: since it typecasts to a char pointer
    magic_char_location = (char *)magic_number_location;

    printf("value magic_number_location references = %p\n", (void *)magic_number_location);
    printf("value magic_char_location references = %p\n", (void *)magic_char_location);

    printf("value magic_char_location references = %d\n", *magic_number_location);
    printf("value magic_char_location references = %c\n", *magic_char_location);

    return 0;
}
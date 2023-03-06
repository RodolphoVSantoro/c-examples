#include <stdio.h>
#define POW_2_26 67108864
#define POW_2_16_TIMES_3 (65536 * 3)
#define POW_2_9 512
#define POW_2_0 1
#define One_every_8_bytes POW_2_26 + POW_2_16_TIMES_3 + POW_2_9 + POW_2_0

int main() {
    int magic_number_array[] = {42, One_every_8_bytes, 1024};

    int *magic_number_location = magic_number_array;

    printf("value magic_number_location references 0 = magic_number_array[0] = %d\n", *magic_number_location);

    magic_number_location++;
    printf("value magic_number_location references 1 = magic_number_array[1] = %d\n", *magic_number_location);

    magic_number_location++;
    printf("value magic_number_location references 2 = magic_number_array[2] = %d\n", *magic_number_location);

    // Since magic_number_array has size 3 ints, DO NOT DO THIS:
    // magic_number_location++;
    // It may work, but it may also cause a segmentation fault.
    // Even if it works, it is not guaranteed to work in the future.
    // Even if it never breaks, it most likely results in reading thrash memory.
    // This is what we call undefined behavior.
    // printf("value magic_number_location references = %d", *magic_number_location);

    char *magic_char_location = (char *)(&magic_number_array[1]);
    printf("value magic_char_location references = %d\n", *magic_char_location);

    magic_char_location++;
    printf("value magic_char_location references = %d\n", *magic_char_location);

    magic_char_location++;
    printf("value magic_char_location references = %d\n", *magic_char_location);

    magic_char_location++;
    printf("value magic_char_location references = %d\n", *magic_char_location);
    return 0;
}
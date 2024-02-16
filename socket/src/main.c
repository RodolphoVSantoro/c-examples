#include <stdio.h>

#include "sock.h"

#include <stdlib.h>

typedef char *str;
#define VEC_TYPE str
#define SHOULD_FREE_TYPE 0
#include "vector.h"


int main(void) {
    int result = example_fn();
    printf("result: %d\n", result);
    return 0;
}

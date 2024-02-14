#include <stdio.h>

typedef enum { OK = 0,
               ERROR = -1 } Error;

#define DECLARE_RESULT(type, name) \
    typedef struct {               \
        type result;               \
        Error error;               \
    } name

DECLARE_RESULT(int, int_result);

int_result test() {
    int_result ret = {1, OK};
    return ret;
}

int main() {
    int_result d = test();
    printf("%d %d\n", d.result, d.error);

    return 0;
}
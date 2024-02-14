#include <stdio.h>

typedef enum { OK = 0,
               ERROR = -1 } Error;

#define DECLARE_RESULT(type, name) \
    typedef struct {               \
        type result;               \
        Error error;               \
    } name

DECLARE_RESULT(int, int_result);

DECLARE_RESULT(float, float_result);

int_result test() {
    int_result ret = {1, OK};
    return ret;
}

float_result test2() {
    float_result ret = {1.0, ERROR};
    return ret;
}

int main() {
    int_result d = test();
    printf("%d %d\n", d.result, d.error);
    float_result f = test2();
    printf("%f %d\n", f.result, f.error);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef enum { false = 0,
               true = 1 } bool;

#define toUpperCase(x) (x > 'Z' ? x - 32 : x)

bool IsIsogram(const char *string) {
    if (string[0] == 0) {
        return true;
    }

    char map[30];
    for (int i = 0; i < 30; i++) {
        map[i] = 0;
    }

    map[toUpperCase(string[0]) - 'A'] = 1;

    int i = 1;
    while (string[i] != 0) {
        char upper = toUpperCase(string[i]);
        if (map[upper - 'A']) {
            return false;
        }
        map[upper - 'A'] = 1;
        i++;
    }

    return true;
}

void do_test(char *str, bool expected) {
    bool result = IsIsogram(str);
    if (result != expected) {
        printf("Expected %d, got %d for %s\n", expected, result, str);
        exit(1);
    }
}

int main() {
    do_test("aa", false);
    do_test("abcde", true);
    do_test("", true);
    do_test("a", true);
    do_test("aba", false);
    do_test("aA", false);
    do_test("abcdefghijklmnopqrstuvwxyzA", false);
}
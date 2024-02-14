#include <stdio.h>
#include <stdlib.h>

typedef enum { false = 0,
               true = 1 } bool;
#define N 1024
typedef struct CHAR_STACK {
    char stack[N];
    int pos, top;
} char_stack;

void init_stack(char_stack *st) {
    for (int i = 0; i < N; i++) {
        st->stack[i] = 0;
    }
    st->pos = 0;
    st->top = -1;
}

void push(char_stack *st, char val) {
    st->stack[st->pos] = val;
    st->pos++;
    st->top++;
}

char pop(char_stack *st) {
    if (st->top < 0) {
        printf("Pop on an empty stack");
        exit(1);
    }
    char rt = st->stack[st->top];
    st->top--;
    st->pos--;
    return rt;
}

bool isEmpty(char_stack st) {
    return st.pos == 0;
}

bool isValid(char *s) {
    char_stack st;
    init_stack(&st);
    int i = 0;
    char res;
    while (s[i] != 0) {
        switch (s[i]) {
            case '(':
            case '[':
            case '{':
                push(&st, s[i]);
                break;
            case ')':
                if (isEmpty(st)) {
                    return false;
                }
                res = pop(&st);
                if (res != '(') {
                    return false;
                }
                break;
            case '}':
                if (isEmpty(st)) {
                    return false;
                }
                res = pop(&st);
                if (res != '{') {
                    return false;
                }
                break;
            case ']':
                if (isEmpty(st)) {
                    return false;
                }
                res = pop(&st);
                if (res != '[') {
                    return false;
                }
                break;
        }
        i++;
    }
    return !isEmpty(st);
}

int main() {
    char s[] = "()[]{}";

    printf("%d\n", isValid(s));

    return 0;
}
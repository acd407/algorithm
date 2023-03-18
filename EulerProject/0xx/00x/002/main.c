#include <stdio.h>

#define fib(cur, next)                                                         \
    {                                                                          \
        next += cur;                                                           \
        cur = next - cur;                                                      \
    }

int main() {
    int a = 1, b = 1;
    int sum = 0;
    while (b < 4e6) {
        fib (a, b);
        if (b % 2 == 0)
            sum += b;
    }
    printf ("%d\n", sum);
}

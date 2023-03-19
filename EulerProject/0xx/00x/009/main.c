#include <stdio.h>
int main() {
    for (int a = 1; a < 1000; a++)
        for (int b = 1; b < 1000; b++) {
            int c = 1000 - a - b;
            if (c * c == a * a + b * b) {
                printf ("%d^2 + %d^2 = %d^2", a, b, c);
                return 0;
            }
        }
}
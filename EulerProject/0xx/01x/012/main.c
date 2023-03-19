#include <stdio.h>
int main() {
    int i = 1, j = 2, total = 1;
    while (total <= 500) {
        i += j;
        j++;
        total = 1;
        for (int t = 1; t * t <= i; t++) {
            if (i % t == 0) {
                if (i == t * t)
                    total++;
                else
                    total += 2;
            }
        }
    }
    printf ("%d\n", i);
}
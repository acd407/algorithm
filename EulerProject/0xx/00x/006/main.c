#include <stdio.h>
int main() {
    long long sum1 = 0, sum2 = 0;
    for (int i = 0; i <= 100; i++) {
        sum1 += i * i;
        sum2 += i;
    }
    sum2 *= sum2;
    printf ("%lld", sum2 - sum1);
}
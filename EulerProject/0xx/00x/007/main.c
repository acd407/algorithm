#include <stdio.h>
#include <stdint.h>
#define prime_len 10001

int main () {
    uint64_t prime[prime_len] = {0};
    size_t prime_p = 0;
    uint64_t i = 2;
    while (prime_p < prime_len) {
        for (int elem = 0; elem < prime_p; elem++)
            if (!(i % prime[elem]))
                goto loop;
            prime[prime_p++] = i;
        loop:
            i++;
    }
    printf("%lld\n", prime[prime_len - 1]);
    return 0;
}
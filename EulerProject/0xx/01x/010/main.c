#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    char *mem = malloc(2e6+1);
    memset(mem, 1, 2e6+1);
    mem[0] = mem[1] = 0;
    size_t memp = 0;
    for (int i = 2; i <= 2e6; i++)
        for (int j = 2; j <= 2e6/i; j++)
            mem[i * j] = 0;
    uint64_t sum = 0;
    for (int i = 0; i <= 2e6; i++)
        sum += mem[i]?i:0;
    printf("%lld\n", sum);
}
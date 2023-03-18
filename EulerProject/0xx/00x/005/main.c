#include <stdint.h>
#include <stdio.h>
uint64_t GCD (uint64_t x, uint64_t y) {
    if (y == 0)
        return x;
    return GCD (y, x % y);
}
uint64_t LCM (uint64_t x, uint64_t y) { return x * y / GCD (x, y); }
uint64_t LCMS (uint64_t total, int i) {
    if (i > 1)
        return LCMS (LCM (total, i), i - 1);
    return total;
}
int main() { printf ("%ld", LCMS (1, 20)); }
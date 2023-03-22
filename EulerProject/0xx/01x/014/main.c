#include <stdio.h>
#include <stdint.h>

int func (uint64_t n) {
    int step = 0;
    while (n != 1) {
        step++;
        if (n % 2)
            n = 3 * n + 1;
        else
            n = n / 2;
    }
    return step;
}
int main() {
    int n = 1e6;
    int maxs = 0;
    int maxv = 0;
    while (--n) {
        int step = func (n);
        if (step > maxs) {
            maxs = step;
            maxv = n;
        }
    }
    printf ("%d %d", maxv, maxs);
}
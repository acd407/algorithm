#include <stdio.h>
#include <stdint.h>

uint64_t nCr (uint64_t n, uint64_t r) { // n > r
    double retc = 1, retp = retc;
    while (r > 0) {
        retc *= n--;
        retp *= r--;
    }
    return (uint64_t)(retc/retp);
}

int main () {
	printf("%lld", nCr(40,20));
	return 0;
}
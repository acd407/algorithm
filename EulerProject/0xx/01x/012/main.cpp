#include <fmt/core.h>
#include <stdint.h>
#include <vector>

size_t divisors_num (uint64_t i) {
    uint64_t k = 2, num = 0;
    while (k * k < i) {
        if (i % k == 0)
            num++;
        k++;
    }
    num *= 2;
    if (k * k == i)
        num++;
    return num + 2;
}

int main() {
    uint64_t n = 1;
    while (divisors_num ((n + 1) * n / 2) < 500)
        n++;
    fmt::print ("{}\n{}\n{}\n", n, (n + 1) * n / 2,
                divisors_num ((n + 1) * n / 2));
    return 0;
}
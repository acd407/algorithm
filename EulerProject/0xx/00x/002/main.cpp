#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::vector<uint64_t> fib {1, 1};
    auto sum {fib[0]&0};
    size_t i = 1;
    while (fib[i] + fib[i - 1] < 4e6) {
        fib.push_back (fib[i] + fib[i - 1]);
        i++;
        if (fib[i] % 2 == 0)
            sum += fib[i];
    }
    std::cout << sum << std::endl;
}
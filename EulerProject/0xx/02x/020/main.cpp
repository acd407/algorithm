#include <fmt/core.h>
#include <cstdint>
#include <vector>
#include <algorithm>

void mul(std::vector<char>& bits, uint64_t i) {
    int carry = 0;
    for (auto& j : bits) {
        uint64_t var = uint64_t(j) * i + carry;
        carry = var / 10;
        j = var % 10;
    }
    while (carry) {
        bits.push_back(carry % 10);
        carry /= 10;
    }
}

int main () {
    auto bits = *new std::vector<char>{1};
    for (uint64_t i = 2; i < 100; i++)
        mul(bits, i);
    uint64_t count = 0;
    for (auto i : bits)
        count += i;
    fmt::print("{}\n", count);
    return 0;
}

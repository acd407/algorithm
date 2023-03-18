#include <stdio.h>
#include <vector>
#include <stdint.h>
using std::vector;
int main() {
    vector<uint64_t> prime;
    size_t prime_len = 0;
    for (uint64_t i = 2; prime_len < 10001; i++) {
        for (auto& item : prime)
            if (i % item == 0)
                goto cycle;
        prime.push_back (i);
        prime_len++;
    cycle:;
    }
    printf ("%lld", *(prime.end() - 1));
}
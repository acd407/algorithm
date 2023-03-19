#include <stdio.h>
#include <vector>
#include <stdint.h>
#include <math.h>
using std::vector;
int main() {
    vector<uint64_t> prime {2};
    for (uint64_t i = 3; i < 2e6; i+=2) {
        for (uint64_t index = 0; prime[index] <= sqrt(i); index++)
            if (i % prime[index] == 0)
                goto loop;
        prime.push_back (i);
    loop:;
    }
    uint64_t sum = 0;
    for (auto var : prime)
        sum += var;
    printf("%I64d\n", sum);
}
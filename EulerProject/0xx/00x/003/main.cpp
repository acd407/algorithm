#include <cmath>
#include <cstdio>
#include <vector>
using std::vector;
int main() {
    vector<long long> factor;
    long long num = 600851475143;
    int i = 2;
    while (1) {
        for (i = 2; i < sqrt (num) + 1; i++) {
            if (num % i == 0) {
                factor.push_back (i);
                num /= i;
                goto cycle;
            }
        }
        factor.push_back (num);
        break;
    cycle:;
    }
    long long max = 0;
    vector<long long>::iterator it;
    for (it = factor.begin(); it != factor.end(); it++)
        if (*it > max)
            max = *it;
    printf ("%d", max);
}
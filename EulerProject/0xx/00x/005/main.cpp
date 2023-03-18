#include <vector>
using std::vector;
#include <cstdio>
int main() {
    vector<int> prime;
    vector<int>::iterator it;
    prime.push_back (2);
    for (int i = 2; i <= 20; i++) {
        for (it = prime.begin(); it != prime.end(); it++) {
            if (i % *it == 0)
                goto cycle;
        }
        prime.push_back (i);
    cycle:;
    }
    int total = 1;
    for (it = prime.begin(); it != prime.end(); it++)
        total *= *it;
    printf ("%d", total);
}
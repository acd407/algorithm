#include <cstdio>
#include <cstdlib>
#include "data.h"

struct bignumber {
    char *bit; // 逆序存储
    bignumber() {
        bit = (char *) malloc (52 * 1);
        for (int i = 0; i < 52; i++) {
            bit[i] = '0';
        }
    }
    bignumber (const char *sz) {
        bit = (char *) malloc (52 * 1);
        for (int i = 0; i < 50; i++) {
            bit[i] = sz[50 - i - 1];
        }
        bit[50] = '0';
        bit[51] = '0';
    }
    void add (bignumber v2) {
        int up = 0;
        for (int i = 0; i < 52; i++) {
            bit[i] += v2.bit[i] - 48 + up;
            up = 0;
            if (bit[i] > '9') {
                bit[i] -= 10;
                up = 1;
            }
        }
    }
};

int main() {
    bignumber *bn[100];
    bignumber sum;
    for (int i = 0; i < 100; i++) {
        bn[i] = new bignumber (str[i]);
        sum.add (*bn[i]);
    }
    for (int i = 51; i > 41; i--) {
        putchar (sum.bit[i]);
    }
}
#include <stdio.h>
#include <stdint.h>
#include "data.h"

int main () {
    uint16_t num[52] = {0};
    for (int j = 0; j < 50; j++)
        for (int i = 0; i < 100; i++)
            num[j] += str[i][49 - j] - '0';
    for (int i = 0; i < 51; i++)
        if(num[i]>9){
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    for (int i = 0; i < 10; i++)
        putchar(num[51 - i] + '0');
    return 0;
}
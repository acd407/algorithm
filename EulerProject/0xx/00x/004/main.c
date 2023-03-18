#include <stdbool.h>
#include <stdio.h>
bool isPalindromicNumber (int num) {
    char bits[6] = {0};
    int len = 0;
    for (; num > 0; len++) {
        bits[len] = num % 10;
        num /= 10;
    }
    for (int i = 0; i < len / 2; i++)
        if (bits[i] != bits[len - i - 1])
            return false;
    return true;
}
int main() {
    int max = 0;
    for (int i = 100; i < 1000; i++)
        for (int j = 100; j < 1000; j++)
            if (isPalindromicNumber (i * j) && i * j > max)
                max = i * j;
    printf ("%d", max);
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

inline void swap (int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// 从小到大
void sort (int *arr, int size) {
    if (size == 2) {
        if (*arr > *(arr + 1))
            swap (arr, arr + 1);
        return;
    }
    int *l = arr, *r = arr + size - 1;
    bool cycle = true;
    while (l < r) {
        if (cycle) {
            if (*r < *l) {
                swap (r, l);
                l++;
                cycle = false;
            } else
                r--;
        } else {
            if (*l > *r) {
                swap (l, r);
                r--;
                cycle = true;
            } else
                l++;
        }
    }
    if (l - arr >= 2)
        sort (arr, l - arr);
    if (arr + size - 1 - l >= 2)
        sort (l + 1, arr + size - 1 - l);
}

#define ARRLEN 16

void print (int *arr) {
    static int *array;
    if (arr)
        array = arr;
    for (int i = 0; i < ARRLEN; i++)
        printf (" %d", array[i]);
    putchar ('\n');
}

int main() {
    int array[ARRLEN];
    srand (time (NULL));
    for (int i = 0; i < ARRLEN; i++)
        array[i] = rand() % 64;
    print (array);
    sort (array, ARRLEN);
    print (array);
}

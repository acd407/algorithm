#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ma_mat.h"

int main() {
    double mat[16] = {
        2,  4,  2,  6, 
        4,  9,  6,  15, 
        2,  6,  9,  18, 
        6,  15, 18, 40
    };
    ma_mat mtx = {4, 4, mat};
    ma_pnt(&mtx);
    putchar('\n');
    ma_mat *L = malloc(sizeof(ma_mat));
    ma_mat *U = malloc(sizeof(ma_mat));
    ma_lu(&mtx, L, U);
    ma_pnt(L);
    putchar('\n');
    ma_pnt(U);
    return 0;
}
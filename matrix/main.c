#include <stdio.h>
#include <stdlib.h>
#include "ma_mat.h"

int main() {
    double *mat = (double *)malloc(sizeof(double)*4*5);
    for(int i=0;i<5;i++)
        for(int j=0;j<4;j++)
            mat[i*4+j] = rand()%16;
    ma_mat mtx = {5, 4, mat};
    ma_print(&mtx);
    putchar('\n');
    ma_tr(&mtx);
    ma_print(&mtx);
    putchar('\n');
    return 0;
}
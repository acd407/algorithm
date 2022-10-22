#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    size_t row;
    size_t col;
    double *data;
}ma_mat;

void ma_tsp(ma_mat *src) {
    double tmp;
    if(src->row == src->col) {
        size_t size = src->row;
        for(size_t i=0;i<size;i++)
            for(size_t j=i+1;j<size;j++) {
                tmp = src->data[i*size+j];
                src->data[i*size+j] = src->data[j*size+i];
                src->data[j*size+i] = tmp;
            }
    } else {
        double *mat = (double *)malloc(sizeof(double)*src->row*src->col);
        for(size_t i=0;i<src->row;i++)
            for(size_t j=0;j<src->col;j++)
                mat[i*src->col+j] = src->data[i*src->col+j];
        tmp = src->row;
        src->row = src->col;
        src->col = tmp;
        for(size_t i=0;i<src->row;i++)
            for(size_t j=0;j<src->col;j++)
                src->data[i*src->col+j] = mat[j*src->row+i];
        free(mat);
    }
}

void ma_pnt(ma_mat *src) {
    for(size_t i=0;i<src->row;i++) {
        for(size_t j=0;j<src->col;j++) {
            printf("%g\t", src->data[i*src->col+j]);
        }
        putchar('\n');
    }
}

void ma_swp(ma_mat *src, size_t xr, size_t xc, size_t yr, size_t yc) {
    double tmp = src->data[xr*src->col+xc];
    src->data[xr*src->col+xc] = src->data[yr*src->col+yc];
    src->data[yr*src->col+yc] = tmp;
}

void ma_swp_row(ma_mat *src, size_t r1, size_t r2) {
    for(size_t i=0;i<src->col;i++)
        ma_swp(src, r1, i, r2, i);
}

void ma_swp_col(ma_mat *src, size_t c1, size_t c2) {
    for(size_t i=0;i<src->row;i++)
        ma_swp(src, i, c1, i, c2);
}

void ma_add_row(ma_mat *src, size_t r1, size_t r2, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[r1*src->col+i] += n * src->data[r2*src->col+i];
        if(fabs(src->data[r1*src->col+i])<1e-5)
            src->data[r1*src->col+i] = 0;
    }
}

void ma_add_col(ma_mat *src, size_t c1, size_t c2, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[i*src->col+c1] += n * src->data[i*src->col+c2];
        if(fabs(src->data[i*src->col+c1])<1e-5)
            src->data[i*src->col+c1] = 0;
    }
}

void ma_tms_row(ma_mat *src, size_t r1, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[r1*src->col+i] *= n;
        if(fabs(src->data[r1*src->col+i])<1e-5)
            src->data[r1*src->col+i] = 0;
    }
}

void ma_tms_col(ma_mat *src, size_t c1, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[i*src->col+c1] *= n;
        if(fabs(src->data[i*src->col+c1])<1e-5)
            src->data[i*src->col+c1] = 0;
    }
}

void ma_utm(ma_mat *src) {
    if(src->row != src->col) {
        puts("col != row");
        exit(__LINE__);
    }
    size_t order = src->row;
    for(size_t j=0;j<order-1;j++) {
        if(src->data[j*order+j]==0) { //错误处理
            bool error = true;
            for(size_t k=j;k<order;k++) { //向下寻找
                if(src->data[k*order+j]!=0) {
                    ma_swp_row(src, j, k);
                    *(src->data) = -*(src->data);
                    error = false;
                }
            }
            if(error) {
                for(size_t i=0;i<order;i++)
                    if(src->data[j*order+i]!=0)
                        for(size_t i=0;i<order;i++)
                            if(src->data[i*order+j]!=0)
                                goto fatalerror;
                puts("warning: Pivot is zero.");
                puts("         Can't transform to utm format.");
                puts("         Det is zero.");
                puts("         Try to transpose the matrix.");
                return ;
            fatalerror:
                puts("error: Pivot is zero.");
                puts("       Can't transform to utm format.");
                puts("       Try to transpose the matrix.\nthe last status:\n");
                ma_pnt(src);
                exit(__LINE__);
            }          
        }
        for(size_t i=j+1;i<order;i++) //计算
            ma_add_row(src, i, j, -src->data[i*src->col+j]/src->data[j*src->col+j]);
    }
}

double ma_det(ma_mat *src) {
    if(src->row != src->col) {
        puts("col != row");
        exit(__LINE__);
    }
    ma_utm(src);
    double total = 1;
    for(size_t i=0;i<src->row;i++)
        total *= src->data[i*src->col+i];
    return total;
}

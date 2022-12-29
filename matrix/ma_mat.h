#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define TOLERANCE 1e-6

typedef struct {
    size_t row;
    size_t col;
    double *data;
}ma_mat;

// functions declared here
ma_mat *ma_new(size_t row, size_t col);
ma_mat *ma_new_m(size_t row, size_t col);
ma_mat *ma_cpy(ma_mat *src);
void ma_swp(ma_mat *src, size_t xr, size_t xc, size_t yr, size_t yc);
void ma_swp_row(ma_mat *src, size_t r1, size_t r2);
void ma_swp_col(ma_mat *src, size_t c1, size_t c2);
void ma_add_row(ma_mat *src, size_t r1, size_t r2, double n);
void ma_add_col(ma_mat *src, size_t c1, size_t c2, double n);
void ma_tms_row(ma_mat *src, size_t r1, double n);
void ma_tms_col(ma_mat *src, size_t c1, double n);
void ma_tsp(ma_mat *src);
void ma_pnt(ma_mat *src);
void ma_utm(ma_mat *src);
double ma_det(ma_mat *src);
void ma_lu(ma_mat *src, ma_mat *L, ma_mat *U);
// unrealized functions
ma_mat *ma_pls(ma_mat *A, ma_mat *B);
ma_mat *ma_tms(ma_mat *A, ma_mat *B);
void ma_add(ma_mat *dest, ma_mat *src);
void ma_mul(ma_mat *dest, ma_mat *src);
void ma_inv(ma_mat *src);
// end

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
            printf("%.4g\t", src->data[i*src->col+j]);
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
        if(fabs(src->data[r1*src->col+i])<TOLERANCE)
            src->data[r1*src->col+i] = 0;
    }
}

void ma_add_col(ma_mat *src, size_t c1, size_t c2, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[i*src->col+c1] += n * src->data[i*src->col+c2];
        if(fabs(src->data[i*src->col+c1])<TOLERANCE)
            src->data[i*src->col+c1] = 0;
    }
}

void ma_tms_row(ma_mat *src, size_t r1, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[r1*src->col+i] *= n;
        if(fabs(src->data[r1*src->col+i])<TOLERANCE)
            src->data[r1*src->col+i] = 0;
    }
}

void ma_tms_col(ma_mat *src, size_t c1, double n) {
    for(size_t i=0;i<src->col;i++) {
        src->data[i*src->col+c1] *= n;
        if(fabs(src->data[i*src->col+c1])<TOLERANCE)
            src->data[i*src->col+c1] = 0;
    }
}

ma_mat *ma_new(size_t row, size_t col) {
    ma_mat *ret = malloc(sizeof(ma_mat));
    ret->row = row;
    ret->col = col;
    ret->data = calloc(ret->row*ret->col, sizeof(double));
    return ret;
}

ma_mat *ma_new_m(size_t row, size_t col) {
    ma_mat *ret = malloc(sizeof(ma_mat));
    ret->row = row;
    ret->col = col;
    ret->data = malloc(ret->row*ret->col*sizeof(double));
    return ret;
}

ma_mat *ma_cpy(ma_mat *src) {
    ma_mat *ret = ma_new_m(src->row, src->col);
    memcpy(ret->data, src->data, sizeof(double)*ret->row*ret->col);
    return ret;
}

//仅接受方阵
void ma_utm(ma_mat *src) {
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
    ma_mat *cpy = ma_cpy(src);
    ma_utm(cpy);
    double total = 1;
    for(size_t i=0;i<cpy->row;i++)
        total *= cpy->data[i*cpy->col+i];
    return total;
}

// L->data 和 U->data 需要是NULL, 否则自己管理它们的初始化
// 禁止传野指针, (比如 malloc 初始化的)
void ma_lu(ma_mat *src, ma_mat *L, ma_mat *U) {
    if(src->col!=src->row)
        return ;
    size_t rank = src->col;
    if(!L->data) {
        L->data = calloc(rank*rank, sizeof(double));
        L->col = L->row = rank;
        for(size_t j=0;j<rank;j++)
            L->data[j*rank+j] = 1;
    }
    if(!U->data) {
        U->data = calloc(rank*rank, sizeof(double));
        U->col = U->row = rank;
        for(size_t j=0;j<rank;j++)
            for(size_t k=0;k<rank;k++)
                U->data[j*rank+k] = src->data[j*rank+k];
    }
    for(size_t r=1;r<rank;r++) {
        for(size_t i=r;i<rank;i++)
            L->data[i*rank+r-1] = U->data[i*rank+r-1]/U->data[(r-1)*rank+r-1];
        for(size_t i=r;i<rank;i++) {
            for(size_t j=r;j<rank;j++)
                U->data[i*rank+j] -= U->data[(r-1)*rank+j]*L->data[i*rank+r-1];
            U->data[i*rank+r-1] = 0;
        }
    }
    return ;
}

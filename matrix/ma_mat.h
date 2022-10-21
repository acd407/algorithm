typedef struct {
    size_t row;
    size_t col;
    double *data;
}ma_mat;

void ma_tr(ma_mat *src) {
    double tmp;
    if(src->row == src->col) {
        size_t size = src->row;
        for(int i=0;i<size;i++)
            for(int j=i+1;j<size;j++) {
                tmp = src->data[i*size+j];
                src->data[i*size+j] = src->data[j*size+i];
                src->data[j*size+i] = tmp;
            }
    } else {
        double *mat = (double *)malloc(sizeof(double)*src->row*src->col);
        for(int i=0;i<src->row;i++)
            for(int j=0;j<src->col;j++)
                mat[i*src->col+j] = src->data[i*src->col+j];
        tmp = src->row;
        src->row = src->col;
        src->col = tmp;
        for(int i=0;i<src->row;i++)
            for(int j=0;j<src->col;j++)
                src->data[i*src->col+j] = mat[j*src->row+i];
        free(mat);
    }
}

void ma_print(ma_mat *src) {
    for(int i=0;i<src->row;i++) {
        for(int j=0;j<src->col;j++) {
            printf("%g\t", src->data[i*src->col+j]);
        }
        putchar('\n');
    }
}

double ma_det(ma_mat *src) {
    if(src->row != src->col) {
        puts("error!");
        exit(1);
    }
}
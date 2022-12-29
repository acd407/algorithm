#include "../ma_mat.h"
#include "H:/Matlab/extern/include/mex.h"
#include <stdio.h>
#include <stdlib.h>
void mexFunction(int retc, mxArray **retp, int argc, const mxArray **argp)
{
    if (argc != 1)
    {
        return;
    }
    retc = 1;
    ma_mat src = {0, 0, NULL};
    src.row = mxGetM(argp[0]);
    src.col = mxGetM(argp[0]);
    src.data = mxGetPr(argp[0]);
    ma_mat *maret = ma_cpy(&src);
    ma_utm(maret);
    mxArray *mxret = mxCreateDoubleMatrix(maret->row, maret->col, mxREAL);
    double *retdata = mxGetPr(mxret);
    memcpy(retdata, maret->data, maret->row * maret->col * sizeof(double));
    retp[0] = mxret;
}
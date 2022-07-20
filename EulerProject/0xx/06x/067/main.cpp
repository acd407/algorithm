#include <iostream>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
int Array[]={
#include "p067_triangle.txt"
};
#define width 100
void setmax(int i,int j)
{
    if(j == 0)
        Array[i*(i+1)/2+j] += Array[i*(i-1)/2+j];
    else if(j == i)
        Array[i*(i+1)/2+j] += Array[i*(i-1)/2+j-1];
    else
        Array[i*(i+1)/2+j] += max(Array[i*(i-1)/2+j],Array[i*(i-1)/2+j-1]);
}
int main()
{
    for(int i=1;i<width;i++)
        for(int j=0;j<=i;j++)
            setmax(i,j);
    int maxum = 0;
    for(int i=width*(width-1)/2+0;i<width*(width-1)/2+width;i++)
        if(maxum<Array[i])
            maxum = Array[i];
    cout << maxum;
}
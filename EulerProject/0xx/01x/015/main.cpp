#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
double nCr(double n,double r)
{
    if(n<r)
    {
        cerr<<"'n<r'!"<<endl;
        exit(EXIT_FAILURE);
    }
    double ret = 1;
    while(r>0)
        ret *= n--/r--;
    return ret;
}
double nPr(double n,double r)
{
    if(n<r)
    {
        cerr<<"'n<r'!"<<endl;
        exit(EXIT_FAILURE);
    }
    double ret = 1;
    while(r-->0)
        ret *= n--;
    return ret;
}

int main()
{
    cout<<std::fixed<<nCr(40,20);
}
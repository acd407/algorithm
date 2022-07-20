long long LGCD(long long x,long long y)
{
    if(y == 0)
        return x;
    return LGCD(y,x%y);
}
long long LLCM(long long x,long long y)
{
    return x*y/LGCD(x,y);
}
long long LCMS(long long tot,int i)
{
    if(i>1)
        return LCMS(LLCM(tot,i),i-1);
    return tot;
}
#include <stdio.h>
int main()
{
    printf("%ld",LCMS(2,20));
}
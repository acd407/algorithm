#include <stdio.h>
int main()
{
    for(long long j=0;j<10;j++)
        for(long long k=0;k<10;k++)
            for(long long m=0;m<10;m++)
                for(long long n=0;n<10;n++)
                    for(long long a=0;a<10;a++)
                        for(long long b=0;b<10;b++)
                            if(j*100000+k*10000+m*1000+n*100+a*10+b==j*j*j*j*j+k*k*k*k*k+m*m*m*m*m+n*n*n*n*n+a*a*a*a*a+b*b*b*b*b)
                                printf("%lld\n",j*100000+k*10000+m*1000+n*100+a*10+b);
}
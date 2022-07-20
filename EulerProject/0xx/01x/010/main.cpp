#include <stdio.h>
#include <vector>
using std::vector;
int main()
{
    vector<long long> prime;
    vector<long long>::iterator it;
    long long i,sum = 2;   
    prime.push_back(2);
    for(i=2;i<2e6;i++)
    {
        for(it=prime.begin();it!=prime.end();it++)
        {
            if(i%*it==0)
                goto loop;
        }
        prime.push_back(i);
        sum += i; 
        loop:;
    }         
    printf("%lld",sum);
}
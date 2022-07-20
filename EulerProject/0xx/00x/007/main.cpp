#include <stdio.h>
#include <vector>
using std::vector;
int main()
{
    vector<long long> prime;
    vector<long long>::iterator it;
    long long i;   
    prime.push_back(2);
    for(i=2;i<__LONG_LONG_MAX__&&prime.size()<10001;i++)
    {
        for(it=prime.begin();it!=prime.end();it++)
        {
            if(i%*it==0)
                goto loop;
        }
        prime.push_back(i);  
        loop:;
    }         
    printf("%lld",*(prime.end()-1));
}
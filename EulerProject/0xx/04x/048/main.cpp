#include <iostream>
using namespace std;
typedef unsigned long long u64;
int main()
{
    u64 sum = 0;
    for(u64 i=1;i<=1e3;i++)
    {
        u64 single = 1;
        for(u64 j=0;j<i;j++)
        {
            single *= i;
            single %= 10000000000ull;
        }
        sum += single;
    }
    sum %= 10000000000ull;
    cout<<sum;
}
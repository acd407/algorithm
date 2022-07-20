#include <vector>
#include <cstdio>
using std::vector;
int main()
{
    int sum = 0;
    vector<long long> fib;
    fib.push_back(1);
    fib.push_back(1);
    int i=1;
    while(fib[i]+fib[i-1]<4e6)
    {
        fib.push_back(fib[i]+fib[i-1]);
        i++;
        if(fib[i]%2==0)
            sum += fib[i];
    }
    printf("%d",sum);
}
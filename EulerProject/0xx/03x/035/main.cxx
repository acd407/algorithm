//太慢了1m38.956s
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
bool similar(int x,int y,int len)
{
    if(len==1)
        return false;
    char bits1[len]{0};
    char bits2[len]{0};
    int i = 0;
    while(x>0)
    {
        bits1[i++] = x%10;
        x /= 10;
    }
    i = 0;
    while(y>0)
    {
        bits2[i++] = y%10;
        y /= 10;
    }
    i = 0;
    while(++i<len)
    {
        for(int j=0;j<len-1;j++)
            swap(bits1[j],bits1[j+1]);
        for(int j=0;j<len;j++)
            if(bits1[j]!=bits2[j])
                goto continuetodo;
        return true;
        continuetodo:;
    }
    return false;
}
int main()
{
    vector<int> prime,count;
    prime.reserve(73000);
    count.reserve(73000);
    prime.push_back(2);
    count.push_back(1);
    int i = 3;
    while(i<(int)1e6)
    {
        bool s = true;
        for(auto j=prime.begin();*j<=sqrt(i)&&j!=prime.end();j++)
            if(i%*j==0)
            {    
                s = false;
                break;
            }
        if(s)
        {
            prime.push_back(i);
            count.push_back(1);
            int t = prime.size()-1;
            int len = (int)log10(prime[t]);
            if(similar(i,i,len+1))
                count.back() = -1;
            int floornum = pow(10,len);
            while(prime[--t]>floornum)
                if(similar(i,prime[t],len+1))
                {
                    count.back() += count[t];
                    break;
                }
        }
        i += 2;
    }
    i = prime.size();
    int sum = 0;
    for(int j=0;j<i;j++)
    {
        if(count[j]==-1)
            sum ++;
        if(count[j]==(int)log10(prime[j])+1)
            sum += count[j];
    }
    cout<<sum;
}
/* for(auto j : prime)
    cout<<left<<setw(4)<<j;
cout<<endl;
for(auto j : count)
    cout<<left<<setw(4)<<j;
cout<<endl; */
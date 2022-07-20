#include <iostream>
#include <string>
using namespace std;
string number;//逆序存储
int length = 1;
void mul2()
{
    string::iterator it;
    int up = 0;
    for(it=number.begin();it!=number.end();it++)
    {
        *it -= 48;
        *it *= 2;
        *it += up;
        if(*it>10)
        {
            up = *it/10;
            *it %= 10;
        }
        *it += 48;
    }
    if(up!=0)
    {
        number.push_back(up);
        length++;
    }
}
int main()
{   
    number.push_back('2');
    for(int i=0;i<1000-1;i++)
        mul2();
    long long sum = 0;
    for(int i=0;i<length;i++)
        sum += number[i]-48;
    cout<<sum<<endl;
    sum = 0;
    string::iterator it;
    for(it=number.begin();it!=number.end();it++)
        sum += *it-48;
    cout<<sum<<endl;
}
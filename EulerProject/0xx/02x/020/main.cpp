#include <deque>
#include <iostream>
using namespace std;
class bignum
{
public:
    deque<char> nums;
    void mul(int mulnum)
    {
        deque<char> mulnums;
        while(mulnum)
        {
            mulnums.push_back(mulnum%10);
            mulnum/=10;
        }
        deque<char>::iterator it;
        int bit = 0;
        for(it=mulnums.begin();it!=mulnums.end();it++)
        {
            deque<char> temp(mulsingel(*it));
            for(int i=0;i<bit;i++)
                temp.push_front(0);
            sum(temp);
            bit++;
        }
        nums = sumnums;
        sumnums = {0};
    }
    void print()
    {
        deque<char>::reverse_iterator it;
        for(it=nums.rbegin();it!=nums.rend();it++)
            cout<<(int)*it;
        cout<<endl;
    }
private:
    deque<char> sumnums{0};
    deque<char> mulsingel(char bit)
    {
        deque<char> target(nums);
        deque<char>::iterator it;
        int up = 0;
        for(it=target.begin();it!=target.end();it++)
        {
            *it *= bit;
            *it += up;
            up = 0;
            if(*it>=10)
            {
                up = *it/10;
                *it %= 10;
            }
        }
        if(up)
            target.push_back(up);
        return target;
    }
    void sum(deque<char> addnums)
    {
        if(addnums.size()>sumnums.size())
            for(int i=0,loops=(addnums.size()-sumnums.size());i<loops;i++)
                sumnums.push_back(0);
        int up = 0;
        for(int i=0;i<sumnums.size();i++)
        {
            sumnums[i]+=addnums[i]+up;
            up = 0;
            if(sumnums[i]>9)
            {
                up = 1;
                sumnums[i] -= 10;
            }
        }
        if(up)
            sumnums.push_back(1);
    }
};
int main()
{
    bignum ans;
    ans.nums.push_back(1);
    for(int i=100;i>0;i--)
        ans.mul(i);
    ans.print();
    deque<char>::iterator it;
    int allbits = 0;
    for(it=ans.nums.begin();it!=ans.nums.end();it++)
        allbits += *it;
    cout<<allbits;
}

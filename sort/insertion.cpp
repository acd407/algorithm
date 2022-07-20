#include <iostream>
#include <list>
using namespace std;
//插入排序 O(n^2)
void sort(list<int> &arr)
{
    list<int> buf(arr);
    arr.clear();
    arr.push_back(*(buf.begin()));
    auto i=buf.begin();
    for(i++;i!=buf.end();i++)
    {
        bool inserted = false;
        for(auto j=arr.begin();j!=arr.end();j++)
            if(*i<*j)
            {
                arr.insert(j,*i);
                inserted = true;
                break;
            }
        if(!inserted)
            arr.push_back(*i);
    }
}
int main()
{
    list<int> arr;
    for(int i=0;i<16;i++)
    {
        arr.push_back(rand());
    }
    for(auto i : arr)
        cout<<i<<'\t';
    cout<<endl;
    sort(arr);
    for(auto i : arr)
        cout<<i<<'\t';
    cout<<endl;
}
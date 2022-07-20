#include <string>
using std::string;
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
template<typename typen>
typen GCD(typen x,typen y)
{
    if(y == 0)
        return x;
    return GCD(y,x%y);
}
template<typename typen>
typen LCM(typen x,typen y)
{
    return x*y/GCD(x,y);
}
#define swap(x,y) ((x)^=(y)^=(x)^=(y))
template<typename typen>
void reverse(typen *source,int len)
{
    for(int i=0;i<len/2;i++)
        swap(source[i],source[len-1-i]);
}
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

string strmul(string num1, string num2) 
{
    int l1 = num1.size();
    int l2 = num2.size();
    char *num3 = new char[l1+l2+1]();
    for(int i=l1-1;i>=0;i--)
        for(int j=l2-1;j>=0;j--)
        {
            num3[i+j+1] += (num1[i]-48)*(num2[j]-48);
            if(num3[i+j+1]>9)
            {
                num3[i+j] += num3[i+j+1]/10;
                num3[i+j+1] %= 10;
            }
        }
    for(int i=0;i<l1+l2;i++)
        num3[i] += 48;
    int i = 0;
    while(num3[i]==48)
        i++;
    if(i==l1+l2)
        i--;
    string ret(num3+i);
    delete [](num3);
    return ret;
}

typedef struct//reverse storage
{
    u16 length;
    u32 *bits;
}BN;
void BNmul(BN *target,BN source)
{
    u64 *buff = (u64 *)calloc(target->length*source.length,sizeof(u64));
    for(u16 i=0;i<target->length;i++)
        for(u16 j=0;j<source.length;j++)
        {
            buff[i+j] += (u64)target->bits[i] * source.bits[j];
            if(buff[i+j]>UINT_MAX)
            {
                u32 *ptr = (u32 *)&(buff[i+j]);//higher 32 bits
                buff[i+j+1] += *++ptr;
                *ptr = 0;
            }
        }
    u16 i = 0;
    while(i<target->length*source.length&&buff[i])
        i++;
    u32 *_ = (u32 *)realloc(target->bits,i*sizeof(u32));
    if(target->bits == 0)
        target->bits = _;
    target->length = i;
    for(int j=0;j<i;j++)
        target->bits[j] = (u32)buff[j];
    free(buff);
}
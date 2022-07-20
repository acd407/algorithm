#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
class BN//reverse storage
{
public:
    u16 length = 0;
    u32 *bits;
    void print()
    {
        u16 i = length;
        while(i)
            printf("%08x",bits[--i]);
        printf("\n");
    }
    BN(){};
    BN(int l,u32 *ptr)
    {
        length = l;
        bits = ptr;
    }
    void add(BN);
    void mul(BN);
};

void BN::add(BN source)
{
    u32 *_ = (u32 *)realloc(bits,__max(length,source.length)+1);
    if(bits==0)
        bits = _;
    for(int i=length;i<__max(length,source.length)+1;i++)
        bits[i] = 0;
    for(u16 i=0;i<__max(length,source.length);i++)
    {
        u64 buff = (u64)bits[i]+source.bits[i];
        if(buff>UINT_MAX)
        {
            u32 *ptr = (u32 *)&buff;
            bits[i] = *ptr;
            bits[i+1] += *(ptr+1);
        }
        else
            bits[i] += source.bits[i];
    }
    if(bits[__max(length,source.length)]!=0)
        length = __max(length,source.length)+1;
    else
        length = __max(length,source.length);
}
void operator += (BN &target,BN source)
{
    target.add(source);
}

BN plus(BN target,BN source)
{
    u32 *buff = (u32 *)malloc(sizeof(u32)*target.length);
    for(int i=0;i<target.length;i++)
        buff[i] = target.bits[i];
    target.add(source);
    BN ret;
    ret.length = target.length;
    ret.bits = target.bits;
    target.bits = buff;
    return ret;
}
BN operator + (BN target,BN source)
{
    return plus(target,source);
}

void BN::mul(BN source)
{
    //64位缓冲区
    u64 *buff = (u64 *)calloc(length+source.length,sizeof(u64));
    //主计算
    for(u16 i=0;i<length;i++)
        for(u16 j=0;j<source.length;j++)
        {
            buff[i+j] += (u64)bits[i] * source.bits[j];
            if(buff[i+j]>UINT_MAX)//判断进位
            {
                //用指针取高32位
                u32 *ptr = (u32 *)&(buff[i+j]);
                buff[i+j+1] += *++ptr;//ptr指向低位，ptr+1指向高位
                *ptr = 0;
            }
        }
    //检测大小
    u16 i = 0;
    while(i<length+source.length&&buff[i])
        i++;
    length = i;
    //重新分配内存
    u32 *_ = (u32 *)realloc(bits,i*sizeof(u32));
    if(bits == 0)
        bits = _;
    //拷贝  
    for(int j=0;j<i;j++)
        bits[j] = (u32)buff[j];
    //销毁
    free(buff);
}
void operator *= (BN &target,BN source)
{
    target.mul(source);
}

BN times(BN target,BN source)
{
    u64 *buff = (u64 *)calloc(target.length+source.length,sizeof(u64));
    for(u16 i=0;i<target.length;i++)
        for(u16 j=0;j<source.length;j++)
        {
            buff[i+j] += (u64)target.bits[i] * source.bits[j];
            if(buff[i+j]>UINT_MAX)
            {
                u32 *ptr = (u32 *)&(buff[i+j]);//higher 32 bits
                buff[i+j+1] += *++ptr;
                *ptr = 0;
            }
        }
    u16 i = 0;
    while(i<target.length+source.length&&buff[i])
        i++;
    BN ret;
    ret.bits = (u32 *)malloc(i*sizeof(u32));
    ret.length = i;
    for(int j=0;j<i;j++)
        ret.bits[j] = (u32)buff[j];
    return ret;
    free(buff);
}
BN operator * (BN target,BN source)
{
    return times(target,source);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#pragma comment(compiler,"-DMEMWATCH -DMW_STDIO")
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef struct//reverse storage
{
    u16 length;
    u32 *bits;
}BN;
void mul(BN *target,BN source)
{
    u64 *buff = (u64 *)calloc(target->length+source.length,sizeof(u64));
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
    while(i<target->length+source.length&&buff[i])
        i++;
    u32 *_ = (u32 *)realloc(target->bits,i*sizeof(u32));
    if(target->bits == 0)
        target->bits = _;
    target->length = i;
    for(int j=0;j<i;j++)
        target->bits[j] = (u32)buff[j];
    free(buff);
}
void print(BN source)
{
    while(source.length)
    {
        printf("%08x",source.bits[source.length-1]);
        source.length--;
    }
    printf("\n");
}
int main()
{
    mwInit();
    BN a,b;
    a.bits = (u32 *)malloc((a.length=3)*sizeof(u32));
    a.bits[0] = 0x352f001f;//low
    a.bits[1] = 0x653efda6;//high
    a.bits[2] = 0x5987a6ee;
    b.bits = (u32 *)malloc((b.length=2)*sizeof(u32));
    b.bits[0] = 0xa5ef007f;
    b.bits[1] = 0xdfda258a;
    print(a);
    print(b);
    mul(&a,b);
    print(a);
    fflush(stdout);
    mwTerm();
    free(a.bits);
    free(b.bits);
}
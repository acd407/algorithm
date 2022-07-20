#include "BN.cxx"
int main()
{
    BN a,b,c;
    a.bits = (u32 *)malloc((a.length=3)*sizeof(u32));
    a.bits[0] = 0x352f001f;//low
    a.bits[1] = 0x653efda6;//high
    a.bits[2] = 0x5987a6ee;
    b.bits = (u32 *)malloc((b.length=2)*sizeof(u32));
    b.bits[0] = 0xa5ef007f;
    b.bits[1] = 0xdfda258a;
    a.print();
    b.print();
    c=a*b;
    c.print();
    fflush(stdout);
    free(a.bits);
    free(b.bits);
    free(c.bits);
}
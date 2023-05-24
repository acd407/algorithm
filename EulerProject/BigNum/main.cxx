#include "BN.cxx"
int main()
{
    BN a,b,c;
    a = *new BN{0x352f001f,0x653efda6,0x5987a6ee};
    b = *new BN{0xa5ef007f,0xdfda258a};
    a.print();
    b.print();
    c=a*b;
    c.print();
    fflush(stdout);
    free(a.bits);
    free(b.bits);
    free(c.bits);
}

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isbouncy(unsigned long long num)
{
    char bits[20] = {0};
    int bitp = 0;
    
    while(num>0)
    {
        bits[bitp++] = num%10 + 48;
        num /= 10;
    }
    
    bitp--;
    int signal;
    if(*bits == bits[bitp])
        signal = 0;
    else if(*bits > bits[bitp])
        signal = 1;
    else
        signal = -1;

    while(bitp)
    {
        if(!signal) {
            if((bits[bitp]!=bits[--bitp]))
                return true;
        }else if(signal<0) {
            if((bits[bitp]<bits[--bitp]))
                return true;
        }else {
            if((bits[bitp]>bits[--bitp]))
                return true;
        }
    }
    return false;
}

//int main(int argc, char **argv)
//{
//    printf("%s\n", isbouncy(atoll(argv[1]))?"true":"false");
//    return 0;
//}

int main()
{
    int bouncycount = 0;
    int i = 100;
    for(;(double)bouncycount/i-0.99<1e-9;i++)
    {
        if(isbouncy(i))
            bouncycount++;
    }
    i--;
    printf("bouncy:\t%d\nall:\t%d", bouncycount, i);
    return 0;
}
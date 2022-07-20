#include "../../../BigNum/BN.cxx"
#include <vector>
using std::vector;
int main()
{
    vector<BN> bns(10000);
    //make
    int k=0;
    for(int i=0;i<101;i++)
    {       
        for(int j=0;j<101;j++)
        {
            bns[k].length = 1;
            bns[k].bits = (u32 *)malloc(1*sizeof(u32));
            bns[k].bits[0] = i;
            BN bnbak = bns[k];
            for(int a=0;a<j;a++)
                bns[k] *= bnbak;
            k++;
        }
    }
}
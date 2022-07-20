/*
答案：55
耗时：0.002754秒
*/
#include <cstdio>
#include <cstring>
using namespace std;

char cPrimes[1000000]; //素数表

int main(void)
{
	//筛法计算素数表
	memset(cPrimes, 1, sizeof(cPrimes));
	cPrimes[0] = 0;
	cPrimes[1] = 0;
	for (int i = 2; i < 1000; ++i)
	{
		if (cPrimes[i] == 0)
			continue;
		for (int j = i * i; j < 1000000; j += i)
			cPrimes[j] = 0;
	}
	int nCount = 0;
	for (int i = 2; i < 1000000; ++i) //穷举各数
	{
		if (cPrimes[i] == 0)
			continue;
		int p = i, nLen = 0;
		while (p > 0) //计算这个数的位数
		{
			++nLen;
			p /= 10;
		}
		p = 1;
		for (int k = 1; k < nLen; ++k) //计算循环中用到的10^(nLen-1)
			p *= 10;
		int j = i; //记录循环数
		bool bFind = true;
		for (int k = 1; k < nLen; ++k) //枚举循环数
		{
			j = j / 10 + (j % 10) * p; //计算循环后的数
			if (cPrimes[j] == 0)	   //检查是否是素数
			{
				bFind = false;
				break;
			}
		}
		if (bFind)
			++nCount; //满足要求
	}
	printf("%d\n", nCount);
	return 0;
}
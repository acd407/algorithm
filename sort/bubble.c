#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define swap(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
#define LEN 1024

struct timespec timestart = {0,0};
struct timespec timeend = {0,0};


void sort(int *, int);
int main()
{
	int *source = (int *)malloc(LEN*sizeof(int));
	for(int i=0;i<LEN;i++)
		source[i] = rand();
	int i = 0;
	clock_gettime(CLOCK_REALTIME,&timestart);
	sort(source, LEN);
	clock_gettime(CLOCK_REALTIME,&timeend);
	while(i<LEN)
	{
		printf("%d\t", source[i]);
		i++;
	}
	printf("\n%lf ms",(double)(timeend.tv_sec-timestart.tv_sec)*1000+(double)(timeend.tv_nsec-timestart.tv_nsec)/1000000);
	return 0;
}
//冒泡排序 O(n^2)
void sort(int *s, int l)
{
	int count;
	while(1)
	{
		count = 0;
		for(int i=0;i<l-1;i++)
			if(s[i]>s[i+1])
				swap(s[i],s[i+1]),count++;
		if(!count)
			break;
	}
}
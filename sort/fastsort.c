#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LEN 1024

struct timespec timestart = {0,0};
struct timespec timeend = {0,0};
void QuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
                j--;
            if(i < j)
                arr[i++] = arr[j];
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
                i++;
            if(i < j)
                arr[j--] = arr[i];
        }
        arr[i] = k;
 
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

int main()
{
	int *source = (int *)malloc(LEN*sizeof(int));
    for(int i=0;i<LEN;i++)
	source[i] = rand();
    clock_gettime(CLOCK_REALTIME,&timestart);
	QuickSort(source, 0, LEN);
    clock_gettime(CLOCK_REALTIME,&timeend);
    int i = 0;
	while(i<LEN)
	{
		printf("%d\t", source[i]);
		i++;
	}
    printf("\n%lf ms",(double)(timeend.tv_sec-timestart.tv_sec)*1000+(double)(timeend.tv_nsec-timestart.tv_nsec)/1000000);
	return 0;
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void sort_1(int *arr, int low, int high)
{
    if (low < high) {
        int i = low, j = high, k = arr[low];
        while (i < j) {
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
        sort_1(arr, low, i - 1);     // 排序k左边
        sort_1(arr, i + 1, high);    // 排序k右边
    }
}

void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//从小到大
void sort_2(int *arr, int size)
{
	if (size == 2) {
		if (*arr > *(arr+1))
			swap(arr, arr+1);
		return;
	}
	int *l = arr, *r = arr + size - 1;
	bool cycle = true;
	while (l < r) {
		if (cycle) {
			if (*r < *l) {
				swap(r, l);
				l++;
				cycle = false;
			} else
				r--;
		} else {
			if (*l > *r) {
				swap(l, r);
				r--;
				cycle = true;
			} else
				l++;
		}
	}
	if (l-arr >= 2)
		sort_2(arr, l-arr);
	if (arr+size-1-l >= 2)
		sort_2(l+1, arr+size-1-l);
}

#define LEN 256*1024
struct timespec timestart = {0,0};
struct timespec timeend = {0,0};

int main()
{
	int *source = (int *)malloc(LEN*sizeof(int));
	size_t seed = time(NULL);
	
    srand(seed);
    for(int i=0;i<LEN;i++)
        source[i] = rand();
    clock_gettime(CLOCK_REALTIME,&timestart);
	sort_1(source, 0, LEN);
    clock_gettime(CLOCK_REALTIME,&timeend);
    printf("%lf ms\n",(double)(timeend.tv_sec-timestart.tv_sec)*1000+(double)(timeend.tv_nsec-timestart.tv_nsec)/1000000);
	
	srand(seed);
    for(int i=0;i<LEN;i++)
        source[i] = rand();
    clock_gettime(CLOCK_REALTIME,&timestart);
	sort_2(source, LEN);
    clock_gettime(CLOCK_REALTIME,&timeend);
    printf("%lf ms\n",(double)(timeend.tv_sec-timestart.tv_sec)*1000+(double)(timeend.tv_nsec-timestart.tv_nsec)/1000000);

	return 0;
}
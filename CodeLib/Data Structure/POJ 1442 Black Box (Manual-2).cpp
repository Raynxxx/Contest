#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

const int maxN = 30010;

void mins_heap(int val,int *arr,int v)
{
	int i;
	for(i = v;i / 2 > 0 && val < arr[i >> 1];i /= 2)
		arr[i] = arr[i >> 1];
	arr[i] = val;
}
void maxs_heap(int val,int *arr,int v)
{
	int i;
	for(i = v;i / 2 > 0 && val > arr[i >> 1];i /= 2)
		arr[i] = arr[i >> 1];
	arr[i] = val;
}
void minx_heap(int val,int *arr,int v)
{
	int i;
	for(i = 1;i * 2 <= v;)
    {
		int t  = 0;
		if(arr[i << 1] < val && arr[i << 1] < arr[(i << 1) + 1])
			arr[i] = arr[i << 1];
		else if((i << 1) + 1 <= v && arr[(i << 1) + 1] < val)
		{
			arr[i] = arr[(i << 1) + 1];
			t = 1;
		}
		else
			break;
		i = (i << 1) + t;
	}
	arr[i] = val;
}
void maxx_heap(int val,int *arr,int v)
{
	int i;
	for(i = 1;i * 2 <= v;)
    {
		int t  = 0;
		if(arr[i << 1] > val && arr[i << 1] > arr[(i << 1) + 1])
			arr[i] = arr[i << 1];
		else if((i << 1) + 1 <= v && arr[(i << 1) + 1] > val)
		{
			arr[i] = arr[(i << 1) + 1];
			t = 1;
		}
		else
			break;
		i = (i << 1) + t;
	}
	arr[i] = val;
}

int main()
{
	int m, n, key[maxN], min_arr[maxN], max_arr[maxN];
	while(~scanf("%d%d", &n, &m))
	{
		for(int i = 1;i <= n; ++ i)
			scanf("%d", &key[i]);
		int c, st = 1;
		for(int i = 1;i <= m; ++ i)
		{
			scanf("%d", &c);
			while(st <= c)
            {
				maxs_heap(key[st], max_arr, i);
				mins_heap(max_arr[1], min_arr, st - i + 1);
				maxx_heap(max_arr[i], max_arr, i - 1);
				st ++;
			}
			printf("%d\n",  min_arr[1]);
			maxs_heap(min_arr[1], max_arr, i);
			minx_heap(min_arr[st - i], min_arr, st - i);
		}
	}
}

/*
** POJ 2299 Ultra-QuickSort
** Created by Rayn @@ 2014/3/24
** 用归并排序来计算逆序数
*/
#include <cstdio>
#include <cstring>
#define MAX 500010

long long ans = 0;
long long arr[MAX], tmp[MAX];

void Merge(long long a[], int l, int m, int r)
{
    int k = 0, i = l, j = m + 1;

    while(i<=m && j<=r)
    {
        if(a[i] < a[j])
        {
            //ans += r - l - (m + 1 - i);
            tmp[k++] = a[i++];
        }
        else
        {
            tmp[k++] = a[j++];
            ans += m - i + 1;
        }
    }
    while(i <= m)
        tmp[k++] = a[i++];
    while(j <= r)
        tmp[k++] = a[j++];

    for(i=0; i<k; ++i)
        a[l+i] = tmp[i];
}
void MergeSort(long long a[], int l, int r)
{
    if(l >= r)
        return ;
    int m = (l + r) / 2;
    MergeSort(a, l, m);
    MergeSort(a, m+1, r);
    Merge(a, l, m, r);
}
int main()
{
    int n;

    while(scanf("%d", &n) != EOF && n)
    {
        memset(tmp, 0, sizeof(tmp));

        for(int i=0; i<n; ++i)
            scanf("%lld", &arr[i]);

        ans = 0;
        MergeSort(arr, 0, n-1);
        /*test for merge_sort
        for(int i=0; i<n; ++i)
            printf("%lld ", arr[i]);
        printf("\n");
        //*/
        printf("%lld\n", ans);
    }
    return 0;
}

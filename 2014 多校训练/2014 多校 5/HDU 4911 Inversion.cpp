/*
** HDU 4911 Inversion
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100005;

int arr[MAXN], tmp[MAXN];
long long cnt, k;

void Merge(int a[], int left, int mid, int right)
{
    int i = left, j = mid + 1;
    int k = 0;
    while(i <= mid && j <= right)
    {
        if(a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            cnt += (LL)mid - i + 1;
        }
    }
    while(i <= mid) {
        tmp[k++] = a[i++];
    }
    while(j <= right) {
        tmp[k++] = a[j++];
    }
    for(i = 0; i < k; ++i) {
        a[left+i] = tmp[i];
    }
}
void MergeSort(int a[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(a, left, mid);
        MergeSort(a, mid+1, right);
        Merge(a, left, mid, right);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d%I64d", &n, &k) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &arr[i]);
        }
        cnt = 0LL;
        MergeSort(arr, 0, n-1);
        printf("%I64d\n", max(cnt-k, 0LL));
    }
    return 0;
}

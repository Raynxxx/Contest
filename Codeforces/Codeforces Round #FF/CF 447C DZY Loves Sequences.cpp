/*
** CodeForces 447C DZY Loves Sequences
** Created by Rayn @@ 2014/07/14
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 100010;

int arr[MAXN];
int l[MAXN], r[MAXN];
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &arr[i]);
        }
        l[0] = 1;
        for(int i = 1; i < n; ++i)
        {
            if(arr[i] > arr[i-1])
                l[i] = l[i-1] + 1;
            else
                l[i] = 1;
        }
        r[n-1] = 1;
        for(int i = n-2; i >= 0; --i)
        {
            if(arr[i] < arr[i+1])
                r[i] = r[i+1] + 1;
            else
                r[i] = 1;
        }
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            ans = max(ans, max(l[i], r[i]));
        }
        for(int i = 1; i < n; i++)
        {
            ans = max(ans, l[i-1] + 1);
        }
        for(int i = 0; i < n-1; i++)
        {
            ans = max(ans, r[i+1] + 1);
        }
        for(int i = 1; i < n-1; i++)
        {
            if(arr[i+1] > arr[i-1] + 1)
                ans = max(ans, l[i-1] + r[i+1] + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}

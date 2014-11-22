/*
** POJ 1631 Bridging signals
** Created by Rayn @@ 2014/05/06
** 最长上升子序列(LIS)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 40010;

int ans, arr[MAX], dp[MAX];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int t, n;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i=1; i<=n; ++i)
            scanf("%d", &arr[i]);

        memset(dp, 0, sizeof(dp));
        ans = 0;
        dp[ans++] = arr[1];
        for(int i=2; i<=n; ++i)
        {
            if(arr[i] > dp[ans-1])
            {
                dp[ans++] = arr[i];
            }
            else
            {
                int *p = lower_bound(dp, dp+ans, arr[i]);
                *p = arr[i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

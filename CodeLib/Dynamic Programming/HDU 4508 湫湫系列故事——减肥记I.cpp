/*
** HDU 4508 湫湫系列故事——减肥记I
** Created by Rayn @@ 2014/04/21
** 完全背包
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 110;

int a[MAXN], b[MAXN];
int dp[100010];

int main()
{
    int n, m;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d", &a[i], &b[i]);
        }
        scanf("%d", &m);
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=n; ++i)
        {
            for(int j=b[i]; j<=m; ++j)
            {
                for(int k=0; j-k*b[i]>=0; ++k)
                {
                    dp[j] = max(dp[j], dp[j-k*b[i]]+k*a[i]);
                }
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

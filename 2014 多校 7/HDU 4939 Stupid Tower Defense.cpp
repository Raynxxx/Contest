/*
** HDU 4939 Stupid Tower Defense
** Created by Rayn @@ 2014/08/15
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
typedef long long LL;
using namespace std;

long long dp[1505][1505];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    long long n, x, y, z, t;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%I64d%I64d%I64d%I64d%I64d", &n, &x, &y, &z, &t);
        LL ans = n*x*t;
        memset(dp, 0, sizeof(dp));
        for(LL i = 1; i <= n; i++)
        {
            for(LL j = 0; j <= i; j++)
            {
                if (j == 0)
                    dp[i][j] = dp[i-1][j] + (i-1-j)*y*t;
                else
                    dp[i][j] = max(dp[i-1][j-1] + (i-j)*y*(t+(j-1)*z), dp[i-1][j]+(i-1-j)*y*(t+j*z));
                ans = max(ans, dp[i][j] + (n-i)*(j*z+t)*(x+(i-j)*y));
            }
        }
        printf("Case #%d: %I64d\n", ++cases, ans);
    }
}

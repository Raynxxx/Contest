/*
** ZOJ 3558 How Many Sets III
** Created by Rayn @@ 2014/05/17
*/
#include <cstdio>
typedef long long LL;
LL MOD = 100000007;

/* 求a到b的和 */
LL getSum(LL a, LL b)
{
    return ((a + b) * (b - a + 1) / 2) % MOD;
}
int main()
{
    LL n, d, mx, x, ans;
    while(scanf("%lld", &n) != EOF)
    {
        ans = 0;
        for(d = 1; d <= n-1; d = x + 1)
        {
            mx = (n - 1) / d;
            x = (n - 1) / mx;
            ans += getSum(1, mx) * getSum(d, x) % MOD;
            ans -= ((mx+1) * getSum(d, x) % MOD - (x-d+1) * n % MOD) * mx % MOD;
            ans = (ans % MOD + MOD) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

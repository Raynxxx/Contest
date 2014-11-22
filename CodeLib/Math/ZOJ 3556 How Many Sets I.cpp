/*
** ZOJ 3558 How Many Sets I
** Created by Rayn @@ 2014/05/22
*/
#include <cstdio>
typedef long long LL;
LL MOD = 1000000007;

LL QuickPow(int n, int k)
{
    LL res = 1, a = n;
    while(k)
    {
        if(k & 1)
            res = res*a % MOD;
        a = a*a % MOD;
        k >>= 1;
    }
    return res;
}
int main()
{
    int n, k;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        LL res = QuickPow(2, k) - 1;
        res = (res + MOD) %  MOD;
        res = QuickPow(res, n);
        printf("%lld\n", res);
    }
    return 0;
}

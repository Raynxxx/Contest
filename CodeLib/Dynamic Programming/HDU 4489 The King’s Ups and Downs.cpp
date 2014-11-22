/*
** HDU 4489 The King¡¯s Ups and Downs
** Created by Rayn @@ 2014/04/26
*/
#include <cstdio>
#include <cmath>
#include <cstring>
typedef long long LL;

LL dp[21];
LL pow(int n)
{
    LL sum = 1;
    for(int i=2; i<=n; ++i)
    {
        sum *= i;
    }
    return sum;
}
LL C(int m, int n)
{
    return pow(n)/(pow(m)*pow(n-m));
}
int main()
{
    int p, cases, n;

    memset(dp, 0, sizeof(dp));
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for(int i=4; i<=20; ++i)
    {
        dp[i] += dp[i-1];
        for(int j=1; j<i-1; ++j)
        {
            if(j==1 || i-1-j==1)
                dp[i] += (dp[j] * dp[i-j-1] >> 1) * C(j, i-1);
            else
                dp[i] += (dp[j] >> 1) * (dp[i-j-1] >> 1) * C(j, i-1);
        }
    }
    ///*
    for(int i=1; i<=20; ++i)
        printf("%d : %I64d\n",i, dp[i]);
    //*/
    scanf("%d", &p);
    while(p--)
    {
        scanf("%d%d", &cases, &n);
        printf("%d %I64d\n", cases, dp[n]);
    }
    return 0;
}

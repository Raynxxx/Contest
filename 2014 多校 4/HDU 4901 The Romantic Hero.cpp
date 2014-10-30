/*
** HDU 4901 The Romantic Hero
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
#define MOD 1000000007
const int MAXN = 1005;
const int MAXA = 1024;
int dp1[MAXN][MAXA], dp2[MAXN][MAXA], dp3[MAXN][MAXA];
int arr[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n, t;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }
        memset(dp1, 0, sizeof(dp1));
        memset(dp2, 0, sizeof(dp2));
        memset(dp3, 0, sizeof(dp3));
        dp1[0][arr[0]] = 1;
        for(int i = 1; i < n-1; i++)
        {
            dp1[i][arr[i]]++;   //单独一个元素构成一个集合
            for(int j = 0; j < MAXA; j++)
            {
                if(dp1[i-1][j])
                {
                    dp1[i][j] += dp1[i-1][j];   //不添加第i个元素进行异或,继承之前算好的
                    dp1[i][j] %= MOD;

                    t = j ^ arr[i];
                    dp1[i][t] += dp1[i-1][j];   //添加第i个元素进行异或
                    dp1[i][t] %= MOD;
                }
            }
        }
        dp2[n-1][arr[n-1]] = 1;
        dp3[n-1][arr[n-1]] = 1;
        for(int i = n-2; i > 0; i--)
        {
            dp2[i][arr[i]]++;   //单独一个元素构成一个集合
            dp3[i][arr[i]]++;
            for(int j = 0; j < MAXA; j++)
            {
                if(dp2[i+1][j])
                {
                    dp2[i][j] += dp2[i+1][j];   //不添加第i个元素进行按位与
                    dp2[i][j] %= MOD;

                    t = j & arr[i];   //添加第i个元素进行按位与
                    dp2[i][t] += dp2[i+1][j];
                    dp2[i][t] %= MOD;

                    dp3[i][t] += dp2[i+1][j]; //添加第i个元素进行按位与
                    dp3[i][t] %= MOD;
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < n-1; i++)
        {
            for(int j = 0; j < MAXA; j++)
            {
                if(dp1[i][j] && dp3[i+1][j])
                {
                    ans += ((LL)dp1[i][j] * dp3[i+1][j] % MOD);
                    ans %= MOD;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

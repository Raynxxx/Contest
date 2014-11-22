/*
** ZOJ 3725 Painting Storages
** Created by Rayn @@ 2014/08/16
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
const int MOD = 1000000007;
const int MAXN = 100010;

int power[MAXN];
int dp[MAXN];

void getPower()
{
    power[0] = 1;
    for(int i = 1; i < MAXN; ++i)
    {
        power[i] = (power[i-1] * 2) % MOD;
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    getPower();
    int N, M;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        memset(dp, 0, sizeof(dp));
        dp[M] = 1;
        for(int i = M+1; i <= N; ++i)
        {
            dp[i] = (dp[i-1] * 2) % MOD;
            dp[i] = ((dp[i] + power[i-M-1] - dp[i-M-1]) % MOD + MOD) % MOD;
        }
        printf("%d\n", dp[N]);
    }
    return 0;
}

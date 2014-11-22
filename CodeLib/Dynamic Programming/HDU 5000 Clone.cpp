/*
** HDU 5000 Clone
** Created by Rayn @@ 2014/09/14
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;

const int MAXN = 2010;

int t[MAXN];
LL dp[MAXN][MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        LL sum = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &t[i]);
            sum += t[i];
        }
        sum /= 2;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= sum; ++j) {
                for(int k = 0; k <= t[i]; ++k) {
                    dp[i][j+k] += dp[i-1][j];
                    dp[i][j+k] %= MOD;
                }
            }
        }
        printf("%d\n", dp[n][sum]);
    }
    return 0;
}

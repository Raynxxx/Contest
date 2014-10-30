/*
** HDU 4944 FSF’s game
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 500010;
const LL MOD = 1LL<<32;

LL dp[MAXN], val[MAXN];

void Cal()
{
    memset(val, 0, sizeof(val));
    for(LL i = 1; i < MAXN; ++i)
    {
        for(LL j = i; j < MAXN; j += i)
        {
            val[j] += (j / i + 1) * (j / i) / 2;
            //val[j] %= MOD;
        }
    }
    dp[1] = 1;
    for(int i = 2; i < MAXN; ++i)
    {
        dp[i] = (dp[i-1] + val[i] * i) % MOD;
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Cal();
    int T, n, cases = 0;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        printf("Case #%d: %I64d\n", ++cases, dp[n]);
    }
    return 0;
}

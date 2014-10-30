/*
** HDU 4945 2048（zip）
** Created by Rayn @@ 2014/08/26
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#define MOD 998244353
using namespace std;
typedef long long LL;
const int MAXN = 100010;
const int MAXM = 2050;

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();

    int x = 0;
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}
inline void fix(LL& x)
{
    while(x < 0) x += MOD;
    while(x >= MOD) x -= MOD;
}
LL quick_pow(LL x, int n)
{
    LL ret = 1;
    while(n)
    {
        if(n & 1)
            ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

int n, is2, cnt[MAXM];
LL dp[MAXM], inv[MAXM];
LL comb[15][MAXM];

inline void PreInit()
{
    inv[1] = 1;
    for(int i = 2; i <= 2048; ++i)
    {
        inv[i] = inv[MOD%i] * (MOD - MOD/i) % MOD;
    }
}
/* 从index这一种类的n个中选出i个的组合数 */
void getComb(int index, int n)
{
    int limit = min(n, 2048/(1<<index));
    comb[index][0] = 1; //comb(n, 0)
    for(int i = 1; i <= limit; ++i) //comb(n, i)
    {
        comb[index][i] = (comb[index][i-1] * (n-i+1) % MOD) * inv[i] % MOD;
    }
}
inline void zip(int x)
{
    for(int i = 0; i+x <= 2048; i += (x<<1))
    {
        dp[i] += dp[i+x];
        fix(dp[i]);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    PreInit();
    int cases = 0;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 1; i <= 2048; i <<= 1) cnt[i] = 0;
        for(int i = 0; i < n; ++i) cnt[nextInt()]++;
        is2 = 0;
        for(int i = 0; i < 12; ++i)
        {
            getComb(i, cnt[1<<i]);
            is2 += cnt[1<<i];
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 0; i < 12; ++i)
        {
            int w = 1 << i;
            for(int j = 2048; j >= 0; j -= w)
            {
                if(dp[j] == 0) continue;
                for(int k = 1; k <= cnt[w]; ++k)
                {
                    if(j + k * w >= 2048) break;
                    dp[j+k*w] += dp[j] * comb[i][k] % MOD;
                    fix(dp[j+k*w]);
                }
            }
            zip(w);
        }
        /*LL res = 0;
        for(int i = 0; i < 2048; ++i)
        {
            res += dp[i];
            fix(res);
        }*/
        LL res = ((quick_pow(2, is2) - dp[0] + MOD) % MOD) * (quick_pow(2, n-is2) % MOD) % MOD;
        fix(res);
        printf("Case #%d: %I64d\n", ++cases, res);
    }
    return 0;
}

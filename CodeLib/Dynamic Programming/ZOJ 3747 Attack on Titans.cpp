/*
** ZOJ 3747 Attack on Titans
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
#define MOD 1000000007
typedef long long LL;
using namespace std;
const int MAXN = 1000010;

int N, M, K;
LL f[MAXN], g[3][MAXN];

void fix(LL& x)
{
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%d", &N, &M, &K) != EOF)
    {
        f[0] = 1;
        for(int i = 1; i <= N; ++i)
        {
            f[i] = (3 * f[i-1]) % MOD;
            if(i == K+1) {
                f[i] = f[i] - 1;
            } else if(i > K+1) {
                f[i] = f[i] - 2 * f[i-K-2];
            }
            fix(f[i]);
        }
        g[0][1] = g[1][1] = g[2][1] = 1;
        if (M == 1)
            g[0][1] = 0;
        for(int i = 2; i <= N; ++ i)
        {
            LL tmp = (g[0][i-1] + g[1][i-1] + g[2][i-1]) % MOD;
            g[0][i] = g[1][i] = g[2][i] = tmp;
            if (i == M) {
                g[0][i] = g[0][i] - 1;
            } else if (i > M) {
                g[0][i] = g[0][i] - g[1][i - M] - g[2][i - M];
            }
            if (i - 1 == K) {
                g[1][i] = g[1][i] - 1;
            } else if (i - 1 > K) {
                g[1][i] = g[1][i] - g[0][i - K - 1] - g[2][i - K - 1];
            }
            fix(g[0][i]); fix(g[1][i]); fix(g[2][i]);
        }
        LL ans = (f[N] - g[0][N] - g[1][N] - g[2][N]) % MOD;
        printf("%lld\n", (ans + MOD) % MOD);
    }
    return 0;
}

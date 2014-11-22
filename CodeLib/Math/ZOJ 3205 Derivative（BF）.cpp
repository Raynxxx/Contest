/*
** ZOJ 3205 Derivative
** Created by Rayn @@ 2014/07/15
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;
const int MAXN = 110;

int n, m, Q;
LL mypow[MAXN][MAXN];
LL C[MAXN], P[MAXN][MAXN], x[MAXN];

void Init()
{
    memset(mypow, 0, sizeof(mypow));
    for(int i = 0; i < MAXN; ++i)
    {
        mypow[i][0] = 1;
    }
    for(int i = 1; i < MAXN; ++i)
    {
        for(int j = 1; j < MAXN; ++j)
        {
            mypow[i][j] = (mypow[i][j-1] * (LL)i) % MOD;
        }
    }
}
void Solve()
{
    for(int i = 0; i < m; ++i)
    {
        LL res = 0;
        for(int j = 0; j < n; ++j)
        {
            if(P[j][i] == 0)
                continue;
            LL tmp = C[j];
            for(int k = 0; k < m; ++k)
            {
                if(k == i)
                {
                    tmp *= mypow[x[k]][P[j][k]-1];
                    tmp %= MOD;
                    tmp *= P[j][k];
                    tmp %= MOD;
                }
                else
                {
                    tmp *= mypow[x[k]][P[j][k]];
                    tmp %= MOD;
                }
            }
            res += tmp;
            res %= MOD;
        }
        printf("%lld%c", res, (i == m-1)? '\n' : ' ');
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
        {
            scanf("%lld", &C[i]);
            for(int j = 0; j < m; ++j)
            {
                scanf("%lld", &P[i][j]);
            }
        }
        scanf("%d", &Q);
        for(int i = 0; i < Q; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                scanf("%lld", &x[j]);
            }
            Solve();
        }
        if(T > 0) {
            printf("\n");
        }
    }
    return 0;
}

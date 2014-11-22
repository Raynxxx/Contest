/*
** ZOJ 3205 Derivative
** Created by Rayn @@ 2014/07/11
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
LL cal[MAXN], ans[MAXN], cnt[MAXN];

void InitPow()
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
void ExGcd(LL a, LL b, LL& x, LL& y, LL& d)
{
    if(!b)
    {
        d = a; x = 1; y = 0;
    }
    else
    {
        ExGcd(b, a%b, y, x, d);
        y -= a / b * x;
    }
}
LL Inv(LL n)
{
    if(n == 0)
        return 1;
    LL d, x, y;
    ExGcd(n, MOD, x, y, d);
    return (x % MOD + MOD) % MOD;
}
void Solve()
{
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++)
    {
        cal[i] = C[i];
        for(int j = 0; j < m; j++)
        {
            if (mypow[x[j]][P[i][j]] > 0)
            {
                cal[i] = cal[i] * mypow[x[j]][P[i][j]];
                cal[i] %= MOD;
            }
            else
            {
                cnt[i] += P[i][j];
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        LL ss = 0;
        for(int j = 0; j < n; j++)
        {
            LL tmp = cal[j];
            if(P[j][i] == 0)
                continue;
            else
            {
                if(cnt[j] == 0)
                {
                    tmp *= P[j][i];
                    tmp %= MOD;
                    tmp *= Inv(x[i]);
                    tmp %= MOD;
                    if(x[i] == 0 && P[j][i] > 1)
                        tmp = 0;
                }
                else if(cnt[j] == 1)
                {
                    if(x[i] != 0)
                        tmp = 0;
                }
                else
                {
                    tmp = 0;
                }
                ss += tmp;
                ss %= MOD;

            }
        }
        ans[i] = ss;
    }
   for(int i = 0;i < m; i++)
   {
       printf("%lld%c", ans[i], (i == m-1)? '\n' : ' ');
   }
}
int main()
{
    InitPow();
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
        while(Q--)
        {
            for(int i = 0; i < m; ++i)
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

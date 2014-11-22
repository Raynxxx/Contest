/*
** ZOJ 3638 Fruit Ninja
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 100000007
typedef long long LL;
using namespace std;

LL QuickMod(LL x, LL n)
{
    LL ans = 1LL;
    while(n)
    {
        if(n&1)
            ans = (ans * x) % MOD;
        x = (x * x) % MOD;
        n /= 2;
    }
    ans %= MOD;
    return ans;
}
LL C(int n, int m)
{
    if(n < m || n < 0 || m < 0)
        return 0;

    LL top = 1, bot = 1;
    for(int i = 0; i < m; ++i)
    {
        top = (top * (LL)(n-i)) % MOD;
        bot = (bot * (LL)(i+1)) % MOD;
    }
    LL res = (top * QuickMod(bot, MOD-2)) % MOD;
    return res;
}
int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m, limit;
    char buf[120], s1[120], s2[120], s3[120];
    int Less[120];

    while(scanf("%d%d%*c", &n, &m) != EOF && n)
    {
        int k = 0;
        while(gets(buf))
        {
            if(strlen(buf) < 3)
                break;
            sscanf(buf, "%s%s%s%d", s1, s2, s3, &limit);
            //printf("%d\n", limit);
            if(s2[0] == 'g')
                m -= (limit + 1);
            else
                Less[k++] = limit;
        }
        if(m < 0)
        {
            printf("0\n");
            continue;
        }
        LL res = 0;
        for(int i = 0; i < (1 << k); ++i)
        {
            int bit = 0, r = 0;
            for(int j = 0; j < k; ++j)
            {
                if(i & (1<<j))
                {
                    bit++;
                    r += Less[j];
                }
            }
            if(bit&1)
                res = (res - C(n+m-r-1, n-1)) % MOD;
            else
                res = (res + C(n+m-r-1, n-1)) % MOD;
            res = (res + MOD) % MOD;
        }
        printf("%lld\n", res);
    }
    return 0;
}

/*
** HDU 4869 Turn the pokers
** Created by Rayn @@ 2014/07/24
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000009
using namespace std;
typedef long long LL;
const int MAXN = 100010;

long long f[MAXN];

void Init()
{
    f[0] = 1;
    for(int i = 1; i < MAXN; ++i)
    {
        f[i] = (f[i-1] * (LL)i) % MOD;
    }
}
LL QuickPow(LL a, LL b)
{
    LL ans = 1;
    while(b > 0)
    {
        if(b&1)
            ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b = b >> 1;
    }
    ans = ans % MOD;
    return ans;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m, x;
    Init();
    while(scanf("%d%d", &n, &m) != EOF)
    {
        int low = 0, high = 0;
        int t1, t2;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &x);
            if(x <= low)
                t1 = low - x;
            else if(x <= high)
                t1 = ((low%2) == (x%2))? 0 : 1;
            else
                t1 = x - high;

            if(high + x <= m)
                t2 = high + x;
            else if(low + x <= m)
                t2 = (((low+x)%2) == (m%2))? m : m-1;
            else
                t2 = 2 * m - (low + x);

            low = t1;
            high = t2;
        }
        long long sum = 0;
        for(int i = low; i <= high; i+=2)
        {
            sum += ((f[m] % MOD) * QuickPow((f[i]*f[m-i]) % MOD, MOD-2)) % MOD;
        }
        printf("%I64d\n", sum % MOD);
    }
    return 0;
}

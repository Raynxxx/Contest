/*
** ZOJ 3647 Gao the Grid
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;

LL C(int n, int m)
{
    if(n < m || m <= 0)
        return 0;
    LL ans = 1, tmp = n;
    for(int i = 0; i < m; ++i)
    {
        ans = ans * tmp;
        tmp--;
    }
    for(int i = 1; i <= m; ++i)
    {
        ans = ans / (LL)i;
    }
    return ans;
}
int main() {

#ifdef HotWhite
    //freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        LL ans = C((n+1)*(m+1), 3);
        //printf("%lld\n", ans);
        ans -= C(n+1, 3) * (m+1);
        ans -= C(m+1, 3) * (n+1);
        for(int i = 2; i <= n; ++i)
        {
            for(int j = 2; j <= m; ++j)
            {
                ans -= (LL)(__gcd(i, j) - 1) * (n+1-i) * (m+1-j) * 2;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

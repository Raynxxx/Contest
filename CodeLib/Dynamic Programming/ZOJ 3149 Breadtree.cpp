/*
** ZOJ 3149 Breadtree
** Created by Rayn @@ 2014/08/02
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100005;
const int MAXW = 1234567890;

int n, k;
LL dp[MAXN];

LL Solve()
{
    dp[1] = 0;
    for(int i = 2; i <= n; ++i)
    {
        dp[i] = (LL)i-1;    //根的重量为i-1
        //每个子树分别相当于i-1,...,i-k年的子树
        for(int j = max(1, i-k); j < i; ++j)
        {
            dp[i] += dp[j];
        }
        if(dp[i] > MAXW) {
            return dp[i];
        }
    }
    return dp[n];
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &n, &k) != EOF && n)
    {
        if(k == 0)
        {
            printf("%d\n", min(MAXW+1, n-1));
            continue;
        }
        LL res = Solve();
        printf("%lld\n", res);
    }
    return 0;
}

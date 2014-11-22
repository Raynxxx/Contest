/*
** HDU 2546 饭卡
** Created by Rayn @@ 2014/08/17
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
typedef long long LL;
using namespace std;
const int MAXN = 1010;

int n, m;
int price[MAXN];
int dp[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &price[i]);
        }
        scanf("%d", &m);
        if(m < 5)
        {
            printf("%d\n", m);
            continue;
        }
        memset(dp, 0, sizeof(dp));
        sort(price, price+n);
        for(int i = 0; i < n-1; ++i)
        {
            for(int j = m-5; j >= price[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - price[i]] + price[i]);
            }
        }
        printf("%d\n", m-dp[m-5]-price[n-1]);
    }
    return 0;
}

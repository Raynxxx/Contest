/*
** ZOJ 3644 Kitty's Game
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;
const int maxn = 2010;
typedef pair<int, int> PII;

int n, m, k;
int u, v;
int p[maxn];
int dp[maxn][maxn];
int re[1000005];
vector<PII> edge;
vector<int> num;

void Init()
{
    edge.clear();
    num.clear();
    memset(re, -1, sizeof(re));
    memset(dp, 0, sizeof(dp));
}
LL lcm(int x, int y)
{
    return (LL)x / __gcd(x, y) * y;
}

int main()
{
    while(scanf("%d%d%d", &n, &m, &k) != EOF)
    {
        Init();
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d", &u, &v);
            edge.push_back(make_pair(u-1, v-1));
        }
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &p[i]);
        }
        for(int i = 1; i <= k; ++i)
        {
            if(k % i == 0)
            {
                re[i] = num.size();
                num.push_back(i);
            }
        }
        if(re[p[0]] == -1)
        {
            printf("0\n");
            continue;
        }
        dp[re[p[0]]][0] = 1;
        for(int i = 0; i < num.size(); ++i)
        {
            vector<PII>::iterator j;
            for(j = edge.begin(); j != edge.end(); ++j)
            {
                int u = j->first;
                int v = j->second;
                LL l = lcm(num[i], p[v]);
                if(l <= 1000000 && re[l] != -1 && l != num[i])
                {
                    dp[re[l]][v] = dp[re[l]][v] + dp[i][u];
                    dp[re[l]][v] %= MOD;
                }
            }
        }
        printf("%d\n", dp[num.size()-1][n-1]);
    }
    return 0;
}

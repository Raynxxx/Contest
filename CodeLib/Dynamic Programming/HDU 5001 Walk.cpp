/*
** HDU 5001 Walk
** Created by Rayn @@ 2014/09/14
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 56;
const int MAXD = 10010;

vector<int> edge[MAXN];

double dp[MAXD][MAXN];
int n, m, d;

void Gao(int u)
{
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i) {
        dp[0][i] = 1.0 / n;
    }
    for(int i = 1; i <= d; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(j == u) continue;
            int sz = edge[j].size();
            for(int k = 0; k < sz; ++k) {
                int v = edge[j][k];
                dp[i][v] += dp[i-1][j] * 1.0 / sz;
            }
        }
    }
    double ret = 0;
    for(int i = 1; i <= n; ++i) {
        if(i != u) {
            ret += dp[d][i];
        }
    }
    printf("%.10f\n", ret);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &d);
        for(int i = 0; i <= n; ++i) edge[i].clear();
        for(int i = 1; i <= m; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        for(int i = 1; i <= n; ++i) {
            Gao(i);
        }
    }
    return 0;
}

/*
** ZOJ 3734 LIKE vs CANDLE
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <climits>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50000 + 10;

int N, X, Y;
int v[MAXN], f[MAXN];
int s[MAXN], p[MAXN];
int dp[MAXN][2][2];
vector<int> G[MAXN];

void Init()
{
    for(int i = 0; i <= N; ++i) {
        G[i].clear();
        dp[i][0][0] = dp[i][0][1] = INT_MIN;
        dp[i][1][0] = dp[i][1][1] = INT_MIN;
    }
}
//flag_pa代表当前节点父亲是否被翻转
//flag_cur代表当前节点父亲是否被Edward翻转
//flag_next代表当前节点的状态
int dfs(int u, int flag_pa, int flag_cur)
{
    if(dp[u][flag_pa][flag_cur] != INT_MIN) {
        return dp[u][flag_pa][flag_cur];
    }
    int flag_next = flag_pa ^ flag_cur ^ s[u];
    int tmp = (flag_next ^ p[u]) ? -v[u] : v[u];
    if(flag_cur) {
        tmp -= s[u] ? Y : X;
    }
    for(int i = 0; i < (int) G[u].size(); ++i) {
        int v = G[u][i];
        tmp += max(dfs(v, flag_next, 0), dfs(v, flag_next, 1));
    }
    return dp[u][flag_pa][flag_cur] = tmp;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d%d", &N, &X, &Y) != EOF)
    {
        Init();
        for(int i = 1; i <= N; ++i) {
            scanf("%d%d%d%d", &v[i], &f[i], &s[i], &p[i]);
            G[f[i]].push_back(i);
        }
        if(dfs(0, 0, 0) < 0) {
            printf("HAHAHAOMG\n");
        } else {
            printf("%d\n", dp[0][0][0]);
        }
    }
	return 0;
}

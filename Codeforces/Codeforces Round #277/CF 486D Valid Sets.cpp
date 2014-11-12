/*
** CF 486D Valid Sets
** Created by Rayn @@ 2014/11/12
*/
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long Long;
typedef vector<int>::iterator Iter;

const int MAXN = 2010;
const int MOD = 1000000007;

vector<int> G[MAXN];
int a[MAXN], dp[MAXN];
bool vis[MAXN];

void Init(int n) {
    for (int i = 0; i <= n; ++i) {
        G[i].clear();
    }
}
void dfs(int u, int root, const int& d) {
    vis[u] = true;
    dp[u] = 1;
    for (Iter it = G[u].begin(); it != G[u].end(); ++it) {
        int v = *it;
        if (!vis[v]) {
            if (a[v] < a[root] || a[v] > a[root] + d) continue;
            if (a[v] == a[root] && v < root) continue;
            dfs(v, root, d);
            dp[u] = ((Long)dp[u] * (dp[v] + 1)) % MOD;
        }
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int d, n;
    while (scanf("%d%d", &d, &n) != EOF) {
        Init(n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int ret = 0;
        for (int i = 1; i <= n; ++i) {
            fill_n(dp, n + 1, 0);
            fill_n(vis, n + 1, false);
            dfs(i, i, d);
            ret = (ret + dp[i]) % MOD;
        }
        printf("%d\n", ret);
    }
    return 0;
}
 
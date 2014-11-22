/*
** ZOJ 3524 Crazy Shopping
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<PII>::iterator Pointer;

const int INF = 0x3F3F3F3F;
const int MAXN = 600 + 10;
const int MAXW = 2000 + 10;

struct Node {
	LL val, cost;
	Node() {}
	Node(LL val, LL cost) : val(val), cost(cost) {}
	inline void Clear() {
		val = cost = 0LL;
	}
};

bool vis[MAXN];
vector<LL> TW, TV;
vector<PII> G[MAXN];
Node dp[MAXN][MAXW];

void PreGao(int n) {
	TW.resize(n + 1);
	TV.resize(n + 1);
	fill(vis, vis + n + 1, false);
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
	}
}
void Gao(int u, int cap) {
	vis[u] = true;
	for (Pointer it = G[u].begin(); it != G[u].end(); ++it) {
		int v = it->first;
		if (vis[v]) continue;
		Gao(v, cap);
	}
	for (int c = cap; c >= 0; --c) {
		dp[u][c].Clear();
		for (Pointer it = G[u].begin(); it != G[u].end(); ++it) {
			int v = it->first;
			int w = it->second;
			if (dp[u][c].val < dp[v][c].val || (dp[u][c].val == dp[v][c].val && dp[v][c].cost + c * w < dp[u][c].cost)) {
				dp[u][c] = Node(dp[v][c].val, dp[v][c].cost + c * w);
			}
		}
		if (c + TW[u] <= cap) {
			if (dp[u][c].val < dp[u][c + TW[u]].val + TV[u]) {
				dp[u][c].val = dp[u][c + TW[u]].val + TV[u];
				dp[u][c].cost = dp[u][c + TW[u]].cost;
			}
			if (dp[u][c].val == dp[u][c + TW[u]].val + TV[u] && dp[u][c].cost > dp[u][c + TW[u]].cost) {
				dp[u][c].cost = dp[u][c + TW[u]].cost;
			}
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m, cap, sx;
	while (scanf("%d%d%d%d", &n, &m, &cap, &sx) != EOF) {
		PreGao(n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &TW[i], &TV[i]);
		}
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(make_pair(v, w));
		}
		Gao(sx, cap);
		printf("%lld\n", dp[sx][0].cost);
	}
	return 0;
}

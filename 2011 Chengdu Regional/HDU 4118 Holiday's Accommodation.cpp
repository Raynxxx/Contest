/*
** HDU 4118 Holiday's Accommodation
** Created by Rayn @@ 2014/11/01
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <map>
#include <stack>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100010;

struct Edge {
	int u, v, w, next;
	Edge() {}
	Edge(int u, int v, int w, int next) : u(u), v(v), w(w), next(next) {}
};

Edge edge[MAXN << 1];
int nEdge, head[MAXN];
int sz[MAXN];
bool vis[MAXN];
Long ret;

void GraphInit(int n) {
	nEdge = 0;
	fill_n(head, n + 5, -1);
}
void AddEdge(int u, int v, int w) {
	edge[nEdge] = Edge(u, v, w, head[u]);
	head[u] = nEdge++;
}
void dfs(int u, int pre, int n) {
	sz[u] = 1;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == pre) continue;
		dfs(v, u, n);
		sz[u] += sz[v];
		Long d = min(sz[v], n - sz[v]);
		ret += edge[i].w * d * 2;
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		GraphInit(n);
		for (int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		fill_n(vis, n + 5, false);
		ret = 0;
		dfs(1, 0, n);
		printf("Case #%d: %I64d\n", ++cases, ret);
	}
	return 0;
}

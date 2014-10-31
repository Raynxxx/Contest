/*
** ACdream 1424 Diversion
** Created by Rayn @@ 2014/10/31
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 20010;
const int MAXM = 100010;
const int INF = 0x3F3F3F3F;

struct Edge {
	int u, v, next;
	Edge() {}
	Edge(int u, int v, int next = 0) : u(u), v(v), next(next) {}
};

class HeavyLightDecompose {
public:
	Edge edge[MAXN << 1];
	int nEdge, head[MAXN];
	int pos, top[MAXN], fa[MAXN], deep[MAXN];
	int num[MAXN], son[MAXN], p[MAXN], fp[MAXN];
	int tag[MAXN];

	void Init(int n) {
		nEdge = pos = 0;
		fill_n(head, n + 3, -1);
		fill_n(son, n + 3, -1);
		fill_n(tag, n + 3, 0);
	}
	void AddEdge(int u, int v) {
		edge[nEdge] = Edge(u, v, head[u]);
		head[u] = nEdge++;
	}
	void dfs_size(int u, int pre, int dep) {
		deep[u] = dep, fa[u] = pre, num[u] = 1;
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (v != pre) {
				dfs_size(v, u, dep + 1);
				num[u] += num[v];
				if (son[u] == -1 || num[v] > num[son[u]]) {
					son[u] = v;
				}
			}
		}
	}
	void Decompose(int u, int tp) {
		top[u] = tp;
		p[u] = ++pos;
		fp[p[u]] = u;
		if (son[u] == -1) return;
		Decompose(son[u], tp);
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (v != son[u] && v != fa[u]) {
				Decompose(v, v);
			}
		}
	}
	void Build() {
		dfs_size(1, 0, 0);
		Decompose(1, 1);
	}
	void Modify(int u, int v) {
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (deep[f1] < deep[f2]) {
				swap(f1, f2);
				swap(u, v);
			}
			++tag[p[f1]];
			--tag[p[u] + 1];
			u = fa[f1];
			f1 = top[u];
		}
		if (u == v) return;
		if (deep[u] > deep[v]) swap(u, v);
		++tag[p[son[u]]];
		--tag[p[v] + 1];
	}
};

HeavyLightDecompose hld;
Edge Road[MAXM];
int RoadCnt;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		hld.Init(n);
		RoadCnt = 0;
		for (int i = 0; i < m; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			if (c == 1) {
				hld.AddEdge(u, v);
				hld.AddEdge(v, u);
			} else {
				Road[RoadCnt++] = Edge(u, v);
			}
		}
		hld.Build();
		for (int i = 0; i < RoadCnt; ++i) {
			hld.Modify(Road[i].u, Road[i].v);
		}
		int way = 0;
		for (int i = 2, cur = 0; i <= n; ++i) {
			cur += hld.tag[i];
			if (cur <= 1) {
				way++;
			}
		}
		printf("%d\n", way);
	}
	return 0;
}

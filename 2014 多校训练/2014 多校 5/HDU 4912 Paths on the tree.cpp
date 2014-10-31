/*
** HDU 4912 Paths on the tree
** Created by Rayn @@ 2014/10/31
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long Long;
const int MAXN = 100010;
const int MAXV = 20;
const int INF = 0x3F3F3F3F;

int nextInt() {
	char ch = getchar();
	bool flag = false;
	while ((ch < '0' || ch > '9') && ch != '-') {
		ch = getchar();
	}
	if (ch == '-') {
		flag = true;
		ch = getchar();
	}
	int ret = 0;
	while (ch >= '0' && ch <= '9') {
		ret = ret * 10 + (ch - '0');
		ch = getchar();
	}
	if (flag) ret = -ret;
	return ret;
}

struct Edge {
	int u, v, next;
	Edge() {}
	Edge(int u, int v, int next) : u(u), v(v), next(next) {}
};

Edge edge[MAXN << 1];
int nEdge, head[MAXN];

class LCA {
public:
	int dep[MAXN];
	int pa[MAXN][MAXV];

	void Init(int n) {
		nEdge = 0;
		fill_n(head, n + 3, -1);
		fill_n(dep, n + 3, 0);
	}
	void AddEdge(int u, int v) {
		edge[nEdge] = Edge(u, v, head[u]);
		head[u] = nEdge++;
	}
	void Build(int u, int fa) {
		dep[u] = dep[fa] + 1;
		pa[u][0] = fa;
		for (int i = 1; i < MAXV; ++i) {
			pa[u][i] = pa[pa[u][i - 1]][i - 1];
		}
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (v != fa) {
				Build(v, u);
			}
		}
	}
	int GetLCA(int u, int v) {
		if (dep[u] > dep[v]) {
			swap(u, v);
		}
		int det = dep[v] - dep[u];
		for (int i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				v = pa[v][i];
			}
		}
		if (u == v) return u;
		for (int i = MAXV - 1; i >= 0; --i) {
			if (pa[u][i] != pa[v][i]) {
				u = pa[u][i];
				v = pa[v][i];
			}
		}
		return pa[u][0];
	}
};

LCA tree;

class Path {
public:
	int u, v, lca;
	bool operator < (const Path& rhs) const {
		return tree.dep[lca] > tree.dep[rhs.lca];
	}
};

Path path[MAXN];
bool mark[MAXN];

void MarkSubTree(int u) {
	if (mark[u]) return;
	mark[u] = true;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == tree.pa[u][0]) continue;
		MarkSubTree(v);
	}
}
int MarkPath(int n, int m) {
	sort(path, path + m);
	fill_n(mark, n + 3, false);
	int ret = 0;
	for (int i = 0; i < m; ++i) {
		if (!mark[path[i].u] && !mark[path[i].v]) {
			ret++;
			MarkSubTree(path[i].lca);
		}
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		tree.Init(n);
		for (int i = 1; i < n; ++i) {
			int u = nextInt();
			int v = nextInt();
			tree.AddEdge(u, v);
			tree.AddEdge(v, u);
		}
		tree.Build(1, 1);
		for (int i = 0; i < m; ++i) {
			path[i].u = nextInt();
			path[i].v = nextInt();
			path[i].lca = tree.GetLCA(path[i].u, path[i].v);
		}
		printf("%d\n", MarkPath(n, m));
	}
	return 0;
}

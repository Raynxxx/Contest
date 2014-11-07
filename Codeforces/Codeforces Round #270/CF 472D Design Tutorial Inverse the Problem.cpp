/*
** CF 472D Design Tutorial Inverse the Problem
** Created by Rayn @@ 2014/10/13
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace FastIO {
	/* Input >> int & long long */
	template <typename T>
	inline void readInteger(T& ret) {
		char ch = getchar();
		bool flag = false;
		while ((ch < '0' || ch > '9') && ch != '-') {
			ch = getchar();
		}
		if (ch == '-') {
			flag = true;
			ch = getchar();
		}
		ret = 0;
		while (ch >= '0' && ch <= '9') {
			ret = ret * 10 + (ch - '0');
			ch = getchar();
		}
		if (flag) ret = -ret;
	}
	inline int nextInt() {
		int x;
		readInteger(x);
		return x;
	}
	inline long long nextLong() {
		long long x;
		readInteger(x);
		return x;
	}
	/* Output << int & long long */
	template <typename T>
	inline void outInteger(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x >= 10) {
			outInteger(x / 10);
		}
		putchar(x % 10 + '0');
	}
};

using namespace std;
using namespace FastIO;

typedef long long LL;
const int MAXN = 2010;

struct Edge {
	int u, v, w;
	int next;
	Edge() {}
	Edge(int u, int v, int w, int next = -1):
		u(u), v(v), w(w), next(next) {}
	bool operator < (const Edge& rhs) const {
		return w < rhs.w;
	}
};

Edge graph[MAXN * MAXN];
Edge tree[MAXN << 1];
int d[MAXN][MAXN];
int c1, c2;
int head[MAXN];
int pa[MAXN];
bool vis[MAXN];
int dist[MAXN];

void Init(int n) {
	c1 = c2 = 0;
	fill_n(head, n + 1, -1);
}
void AddEdge(int u, int v, int w) {
	tree[c2] = Edge(u, v, w, head[u]);
	head[u] = c2++;
}
void MakeSet(int n) {
	for (int i = 0; i <= n; ++i) {
		pa[i] = i;
	}
}
int FindSet(int x) {
	if (x != pa[x])
		pa[x] = FindSet(pa[x]);
	return pa[x];
}
void MST(int n) {
	MakeSet(n);
	sort(graph, graph + c1);
	for (int i = 0; i < c1; ++i) {
		int u = graph[i].u;
		int v = graph[i].v;
		int w = graph[i].w;
		int px = FindSet(u);
		int py = FindSet(v);
		if (px != py) {
			pa[px] = py;
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
	}
}
void dfs(int u, int w) {
	vis[u] = true;
	dist[u] = w;
	for (int i = head[u]; i != -1; i = tree[i].next) {
		int v = tree[i].v;
		if (vis[v]) continue;
		dfs(v, w + tree[i].w);
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n;
	while (scanf("%d", &n) != EOF) {
		Init(n);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				d[i][j] = nextInt();
			}
		}
		if (n == 1 && d[1][1] == 0) {
			puts("YES");
			continue;
		}
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			if (d[i][i] != 0) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			puts("NO");
			continue;
		}
		for (int i = 1; i <= n && flag; ++i) {
			for (int j = i + 1; j <= n && flag; ++j) {
				if (d[i][j] != d[j][i] || d[i][j] == 0) {
					flag = false;
					break;
				}
				graph[c1++] = Edge(i, j, d[i][j]);
			}
		}
		MST(n);
		for (int i = 1; i <= n && flag; ++i) {
			fill_n(vis, n + 1, false);
			dfs(i, 0);
			for (int j = 1; j <= n; ++j) {
				if (!vis[j] || dist[j] != d[i][j]) {
					flag = false;
					break;
				}
			}
		}
		if (flag) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}

/*
** POJ 1741 Tree
** Created by Rayn @@ 2014/10/09
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
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
const int MAXN = 10000 + 10;
const int INF = 0x3F3F3F3F;

struct Edge {
	int v, w, next;
	Edge() {}
	Edge(int v, int w, int next): v(v), w(w), next(next) {}
};

Edge edge[MAXN << 2];
int cnt;
int head[MAXN];
int sz[MAXN];
int dist[MAXN];
bool vis[MAXN];
int Left, Right;

void GraphInit(int n) {
	cnt = 0;
	fill_n(head, n + 2, -1);
	fill_n(vis, n + 2, false);
}
void AddEdge(int u, int v, int w) {
	edge[cnt] = Edge(v, w, head[u]);
	head[u] = cnt++;
}

int Size(int u, int pre) {
	sz[u] = 1;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == pre || vis[v]) continue;
		sz[u] += Size(v, u);
	}
	return sz[u];
}
void FindRoot(int u, int pre, int tot_size, int& mins, int& root) {
	int maxs = tot_size - sz[u];
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == pre || vis[v]) continue;
		FindRoot(v, u, tot_size, mins, root);
		maxs = max(maxs, sz[v]);
	}
	if (maxs < mins) {
		mins = maxs;
		root = u;
	}
}
void DistToRoot(int u, int pre, int d) {
	dist[Right++] = d;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == pre || vis[v]) continue;
		DistToRoot(v, u, d + edge[i].w);
	}
}
int Gao(int l, int r, int limit) {
	sort(dist + l, dist + r);
	int ret = 0, e = r - 1;
	for (int i = l; i < r; ++i) {
		if (dist[i] > limit) break;
		while (e >= l && dist[e] + dist[i] > limit) {
			e--;
		}
		ret += e - l + 1;
		if (e > i) ret--;
	}
	return ret >> 1;
}
int Solver(int u, int limit) {
	int tot_sz = Size(u, -1);
	int root, mins = INF;
	FindRoot(u, -1, tot_sz, mins, root);
	vis[root] = true;
	int ret = 0;
	for (int i = head[root]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (vis[v]) continue;
		ret += Solver(v, limit);
	}
	Left = Right = 0;
	for (int i = head[root]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (vis[v]) continue;
		DistToRoot(v, root, edge[i].w);
		ret -= Gao(Left, Right, limit);
		Left = Right;
	}
	ret += Gao(0, Right, limit);
	for (int i = 0; i < Right; ++i) {
		if (dist[i] <= limit) {
			ret++;
		} else {
			break;
		}
	}
	vis[root] = false;
	return ret;
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF && (n && k)) {
		GraphInit(n);
		for (int i = 1; i < n; ++i) {
			int u = nextInt();
			int v = nextInt();
			int w = nextInt();
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		outInteger(Solver(1, k));
		putchar('\n');
	}
	return 0;
}

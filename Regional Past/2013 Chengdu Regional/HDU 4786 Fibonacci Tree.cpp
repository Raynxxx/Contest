/*
** HDU 4786 Fibonacci Tree
** Created by Rayn @@ 2014/10/27
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
const int MAXN = 100010;

struct Edge {
	int u, v, c;
	Edge() {}
	Edge(int u, int v, int c) : u(u), v(v), c(c) {}
	bool operator < (const Edge& rhs) const {
		return c < rhs.c;
	}
	bool operator > (const Edge& rhs) const {
		return c > rhs.c;
	}
};

Edge edge[MAXN];
int pa[MAXN];
int sz[MAXN];
int fib[64];

void FibInit() {
	fib[0] = 1;
	fib[1] = 2;
	for (int i = 2; i <= 36; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
}
void MakeSet(int n) {
	for (int i = 1; i <= n; ++i) {
		pa[i] = i;
		sz[i] = 1;
	}
}
int FindSet(int x) {
	if (x != pa[x])
		pa[x] = FindSet(pa[x]);
	return pa[x];
}
void UnionSet(int x, int y) {
	if (sz[x] > sz[y]) {
		pa[y] = x;
		sz[x] += sz[y];
	} else {
		pa[x] = y;
		sz[y] += sz[x];
	}
}
int MST(int n, int m, int type) {
	if (type == 0) {
		sort(edge, edge + m, less<Edge>());
	} else {
		sort(edge, edge + m, greater<Edge>());
	}
	MakeSet(n);
	int ret = 0;
	for (int i = 0; i < m; ++i) {
		int px = FindSet(edge[i].u);
		int py = FindSet(edge[i].v);
		if (px != py) {
			ret += edge[i].c;
			UnionSet(px, py);
		}
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	FibInit();
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			edge[i] = Edge(u, v, c);
		}
		int lower = MST(n, m, 0);
		int upper = MST(n, m, 1);
		bool tree = true;
		for (int i = 1; i <= n; ++i) {
			if (FindSet(i) != FindSet(1)) {
				tree = false;
				break;
			}
		}
		printf("Case #%d: ", ++cases);
		int id = lower_bound(fib, fib + 36, lower) - fib;
		if (tree && fib[id] >= lower && fib[id] <= upper) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
	return 0;
}
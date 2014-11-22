/*
** ZOJ 3742 Bellywhite's Algorithm Homework
** Created by Rayn @@ 2014/10/17
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
using namespace std;

typedef long long Long;
const int MAXN = 50050;
const int MAXM = 100050;

struct Edge {
	int u, v, w;
	int next;
	Edge() {}
	Edge(int u, int v, int w, int next) : u(u), v(v), w(w), next(next) {}
	void read() {
		scanf("%d%d%d", &u, &v, &w);
	}
};

Edge edge[MAXN];
Edge graph[MAXM];
int Limit;
int sz, head[MAXN];
int degree[MAXN];
int state[MAXN];
Long sum[MAXN][2];
vector<int> heavy;

void InitGraph(int n, int m) {
	sz = 0;
	Limit = (int)sqrt(m);
	fill_n(head, n + 5, -1);
	fill_n(state, n + 5, 1);
	for (int i = 0; i <= n; ++i) {
		sum[i][0] = sum[i][1] = 0;
	}
}
void AddEdge(int u, int v, int w) {
	graph[sz] = Edge(u, v, w, head[u]);
	head[u] = sz++;
}
void MakeGraph(int n, int m) {
	heavy.clear();
	heavy.push_back(0);
	for (int i = 1; i <= n; ++i) {
		if (degree[i] > Limit) {
			heavy.push_back(i);
		}
	}
	for (int i = 0; i < m; ++i) {
		int u = edge[i].u;
		int v = edge[i].v;
		int w = edge[i].w;
		if (degree[u] > Limit) {
			AddEdge(v, u, w);
			sum[u][w > 0] += w;
		} else if (degree[v] > Limit) {
			AddEdge(u, v, w);
			sum[v][w > 0] += w;
		} else {
			AddEdge(u, v, w);
			AddEdge(v, u, w);
			sum[0][w > 0] += w;
		}
	}
}
void Change(int x) {
	for (int i = head[x]; i != -1; i = graph[i].next) {
		int v = graph[i].v;
		int w = graph[i].w * state[x] * state[v];
		if (degree[v] <= Limit) {
			sum[0][0] -= w;
			sum[0][1] -= w;
		} else {
			sum[v][0] -= w;
			sum[v][1] -= w;
		}
	}
	state[x] = -state[x];
	if (degree[x] > Limit) {
		sum[x][0] = -sum[x][0];
		sum[x][1] = -sum[x][1];
		swap(sum[x][0], sum[x][1]);
	}
}
Long Query(int type) {
	Long ret = 0;
	for (vector<int>::iterator it = heavy.begin(); it != heavy.end(); ++it) {
		ret += sum[*it][type];
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m, q, cases = 0;
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		fill_n(degree, n + 5, 0);
		for (int i = 0; i < m; ++i) {
			edge[i].read();
			degree[edge[i].u]++;
			degree[edge[i].v]++;
		}
		InitGraph(n, m);
		MakeGraph(n, m);
		if (cases++) {
			putchar('\n');
		}
		while (q--) {
			char op[10];
			scanf("%s", op);
			if (op[0] == 'C') {
				int x;
				scanf("%d", &x);
				Change(x);
			} else if (op[0] == 'Q') {
				char cmd[10];
				scanf("%s", cmd);
				Long ret = 0;
				if (cmd[0] == 'A') {
					ret = Query(0) + Query(1);
				} else if (cmd[0] == '+') {
					ret = Query(1);
				} else if (cmd[0] == '-') {
					ret = Query(0);
				}
				printf("%lld\n", ret);
			}
		}
	}
	return 0;
}

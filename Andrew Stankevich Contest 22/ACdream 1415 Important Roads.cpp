/*
** ACdream 1415 Important Roads
** Created by Rayn @@ 2014/10/30
*/
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
typedef pair<int, int> PII;
const int MAXN = 20010;
const int MAXM = 200010;
const int INF = 0x3F3F3F3F;

struct Edge {
	int u, v, w;
	int id, next;
	Edge() {}
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	Edge(int v, int w, int id, int next) : v(v), w(w), id(id), next(next) {}
};

class Dijkstra {
public:
	int n, m;
	Edge edge[MAXM];
	int head[MAXN];
	bool vis[MAXN];

	void Init(int n) {
		this->n = n;
		this->m = 0;
		fill_n(head, n + 3, -1);
	}
	void AddEdge(int u, int v, int w, int id) {
		edge[m] = Edge(v, w, id, head[u]);
		head[u] = m++;
	}
	void work(int st, vector<int>& dis) {
		fill_n(vis, n + 5, false);
		dis.resize(n + 5, INF);
		priority_queue<PII, vector<PII>, greater<PII> > pq;
		dis[st] = 0;
		pq.push(make_pair(dis[st], st));
		while (!pq.empty()) {
			int u = pq.top().second;
			pq.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (dis[v] > dis[u] + edge[i].w) {
					dis[v] = dis[u] + edge[i].w;
					pq.push(make_pair(dis[v], v));
				}
			}
		}
	}
};

struct BCC {
	int n, m;
	int clock;
	Edge edge[MAXM];
	int head[MAXN];
	int dfn[MAXN], low[MAXN];
	bool iscut[MAXM];

	void Init(int n) {
		this->n = n;
		this->m = 0;
		clock = 0;
		fill_n(head, n + 3, -1);
		fill_n(dfn, n + 3, 0);
		fill_n(low, n + 3, 0);
		fill_n(iscut, n + 3, false);
	}
	void AddEdge(int u, int v, int w, int id) {
		edge[m] = Edge(v, w, id, head[u]);
		head[u] = m++;
	}
	void Tarjan(int u, int fa) {
		dfn[u] = low[u] = ++clock;
		bool flag = true;
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (v == fa && flag) {
				flag = false;
				continue;
			}
			if (!dfn[v]) {
				Tarjan(v, u);
				low[u] = min(low[u], low[v]);
				if (low[v] > dfn[u]) {
					iscut[edge[i].id] = true;
				}
			}
			else {
				low[u] = min(low[u], dfn[v]);
			}
		}
	}
	void Find_Bridge(int sz, vector<int>& ret) {
		for (int i = 1; i <= n; ++i) {
			if (!dfn[i]) {
				Tarjan(i, 0);
			}
		}
		ret.clear();
		for (int i = 1; i <= sz; ++i) {
			if (iscut[i]) {
				ret.push_back(i);
			}
		}
		sort(ret.begin(), ret.end());
	}
};


BCC bcc;
Edge road[MAXM];
Dijkstra dijkstra;
vector<int> dist[2];
vector<int> ret;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		dijkstra.Init(n);
		bcc.Init(n);
		for (int i = 1; i <= m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			dijkstra.AddEdge(u, v, w, i);
			dijkstra.AddEdge(v, u, w, i);
			road[i] = Edge(u, v, w);
		}
		dijkstra.work(1, dist[0]);
		dijkstra.work(n, dist[1]);
		Long ShortestPath = dist[0][n];
		for (int i = 1; i <= m; ++i) {
			int u = road[i].u;
			int v = road[i].v;
			if (dist[0][u] + road[i].w + dist[1][v] == ShortestPath ||
				dist[0][v] + road[i].w + dist[1][u] == ShortestPath) {
				bcc.AddEdge(u, v, road[i].w, i);
				bcc.AddEdge(v, u, road[i].w, i);
			}
		}
		bcc.Find_Bridge(m, ret);
		int sz = ret.size();
		printf("%d\n", sz);
		for (int i = 0; i < sz; ++i) {
			printf("%d%c", ret[i], (i == sz - 1) ? '\n' : ' ');
		}
	}
	return 0;
}

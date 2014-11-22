/*
** ZOJ 3425 Similarity
** Created by Rayn @@ 2014/10/10
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

typedef long long LL;
const int MAXN = 80;
const int MAXM = MAXN * MAXN * 2;
const int INF = 0x3F3F3F3F;

class MCMF {
public:
	struct Edge {
		int from, to, cap, flow, cost;
		int next;
		Edge() {}
		Edge(int from, int to, int cap, int flow, int cost, int next):
			from(from), to(to), cap(cap), flow(flow), cost(cost), next(next) {}
	};

	int n, m;
	Edge edge[MAXM];
	int head[MAXN];
	bool inq[MAXN];
	int dis[MAXN];
	int pre[MAXN];
	int low[MAXN];

	void Init(int n) {
		this->n = n;
		this->m = 0;
		memset(head, -1, sizeof(head));
	}
	void AddEdge(int u, int v, int cap, int cost) {
		edge[m] = Edge(u, v, cap, 0, -cost, head[u]);
		head[u] = m++;
		edge[m] = Edge(v, u, 0, 0, cost, head[v]);
		head[v] = m++;
	}
	bool SPFA(int s, int t, int& flow, int& cost) {
		fill_n(inq, MAXN, false);
		fill_n(dis, MAXN, INF);
		queue<int> Q;
		Q.push(s);
		inq[s] = true;
		dis[s] = 0;
		pre[s] = 0;
		low[s] = INF;
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			inq[u] = false;
			for (int i = head[u]; i != -1; i = edge[i].next)
			{
				int v = edge[i].to;
				int w = edge[i].cap - edge[i].flow;
				if (w > 0 && dis[v] > dis[u] + edge[i].cost)
				{
					dis[v] = dis[u] + edge[i].cost;
					pre[v] = i;
					low[v] = min(low[u], w);
					if (!inq[v])
					{
						Q.push(v);
						inq[v] = true;
					}
				}
			}
		}
		if (dis[t] == INF)
			return false;
		flow += low[t];
		cost += low[t] * dis[t];
		int u = t;
		while (u != s)
		{
			edge[pre[u]].flow += low[t];
			edge[pre[u] ^ 1].flow -= low[t];
			u = edge[pre[u]].from;
		}
		return true;
	}
	int MaxCost(int s, int t)
	{
		int flow = 0, cost = 0;
		while (SPFA(s, t, flow, cost));
		return -cost;
	}
};

MCMF net;
int S, T;
int maps[64][64];
char label[10010];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int test;
	int n, m, k;
	scanf("%d", &test);
	while (test--) {
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 1; i <= n; ++i) {
			char str[5];
			scanf("%s", str);
			label[i] = str[0];
		}
		S = 0, T = 53;
		while (m--) {
			net.Init(S + T + 1);
			for (int i = 1; i <= 26; ++i) {
				net.AddEdge(S, i, 1, 0);
				net.AddEdge(i + 26, T, 1, 0);
			}
			memset(maps, 0, sizeof(maps));
			for (int i = 1; i <= n; ++i) {
				char str[5];
				scanf("%s", str);
				maps[label[i] - 'A'][str[0] - 'A']++;
			}
			for (int i = 0; i < 26; ++i) {
				for (int j = 0; j < 26; ++j) {
					if (maps[i][j] > 0) {
						net.AddEdge(i + 1, j + 27, 1, maps[i][j]);
					}
				}
			}
			int ret = net.MaxCost(S, T);
			printf("%.4f\n", (double)ret / n);
		}
	}
	return 0;
}

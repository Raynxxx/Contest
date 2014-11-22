/*
** ZOJ 3348 Schedule
** Created by Rayn @@ 2014/10/18
*/
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <queue>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int MAXM = MAXN * MAXN;
const int INF = 0x3F3F3F3F;

struct Dinic
{
	struct Edge
	{
		int from, to, cap, flow;
		int next;
		Edge() {}
		Edge(int from, int to, int cap, int flow, int next) :
			from(from), to(to), cap(cap), flow(flow), next(next) {}
	};

	int n, m, s, t;
	bool vis[MAXN];
	int d[MAXN];
	int cur[MAXN];
	int head[MAXN];
	Edge edge[MAXM];

	void Init(int n) {
		this->n = n;
		this->m = 0;
		fill_n(head, n + 5, -1);
	}
	void AddEdge(int from, int to, int cap) {
		edge[m] = Edge(from, to, cap, 0, head[from]);
		head[from] = m++;
		edge[m] = Edge(to, from, 0, 0, head[to]);
		head[to] = m++;
	}
	bool bfs() {
		memset(vis, false, sizeof(vis));
		queue<int> Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = true;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (int i = head[u]; i != -1; i = edge[i].next) {
				Edge& e = edge[i];
				if (!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = true;
					d[e.to] = d[u] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}
	int dfs(int x, int a) {
		if (x == t || a == 0) return a;
		int flow = 0, f;
		for (int& i = cur[x]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].cap - edge[i].flow;
			if (d[v] == d[x] + 1 && (f = dfs(v, min(a, w))) > 0) {
				edge[i].flow += f;
				edge[i ^ 1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}
	int MaxFlow(int s, int t) {
		this->s = s; this->t = t;
		int flow = 0;
		while (bfs()) {
			memcpy(cur, head, sizeof(head));
			flow += dfs(s, INF);
		}
		return flow;
	}
};

Dinic Network;
map<string, int> player;
int playerID;

int GetId(const string& name) {
	if (player.find(name) == player.end()) {
		player[name] = playerID++;
	}
	return player[name];
}
void Init() {
	playerID = 0;
	player.clear();
	GetId("DD");
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	char p1[64], p2[64], score[64];
	int n, m, p;
	while (scanf("%d%d", &n, &m) != EOF) {
		Init();
		vector<int> Rank(MAXN, 0);
		vector< vector<int> > play(MAXN, vector<int>(MAXN, 0));
		for (int i = 0; i < m; ++i) {
			scanf("%s%s%s", p1, p2, score);
			int a = GetId(string(p1));
			int b = GetId(string(p2));
			(score[0] == 'w') ? ++Rank[a] : ++Rank[b];
		}
		scanf("%d", &p);
		for (int i = 0; i < p; ++i) {
			scanf("%s%s", p1, p2);
			int a = GetId(string(p1));
			int b = GetId(string(p2));
			if (a > b) swap(a, b);
			++Rank[a];
			++play[a][b];
		}
		if (Rank[0] == 0) {
			puts(n == 1 ? "Yes" : "No");
			continue;
		}
		int S = 0, T = n, all = 0;
		Network.Init(n);
		for (int i = 1; i < n; ++i) {
			all += Rank[i];
			Network.AddEdge(S, i, Rank[i]);
			Network.AddEdge(i, T, Rank[0] - 1);
			for (int j = i + 1; j < n; ++j) {
				Network.AddEdge(i, j, play[i][j]);
			}
		}
		int maxflow = Network.MaxFlow(S, T);
		puts(maxflow == all ? "Yes" : "No");
	}
	return 0;
}

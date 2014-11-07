/*
** HDU 5076 Memory
** Created by Rayn @@ 2014/10/30
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
const int MAXN = 600;
const int MAXM = MAXN * MAXN * 8;
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

struct Dinic {
	struct Edge {
		int from, to, cap, flow;
		int next;
		Edge() {}
		Edge(int from, int to, int cap, int flow, int next) :
			from(from), to(to), cap(cap), flow(flow), next(next) {}
	};

	int n, m, s, t;
	int dis[MAXN];
	int head[MAXN];
	int cur[MAXN];
	Edge edge[MAXM];

	void Init(int n) {
		this->n = n;
		this->m = 0;
		memset(head, -1, sizeof(head));
	}
	void AddEdge(int from, int to, int cap)	{
		edge[m] = Edge(from, to, cap, 0, head[from]);
		head[from] = m++;
		edge[m] = Edge(to, from, 0, 0, head[to]);
		head[to] = m++;
	}
	bool bfs() {
		memset(dis, -1, sizeof(dis));
		queue<int> Q;
		Q.push(s);
		dis[s] = 0;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				int w = edge[i].cap - edge[i].flow;
				if (dis[v] < 0 && w > 0) {
					dis[v] = dis[u] + 1;
					if (v == t) return true;
					Q.push(v);
				}
			}
		}
		return false;
	}
	int dfs(int u, int a) {
		if (u == t || a == 0) return a;
		int flow = 0, f;
		for (int& i = cur[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].cap - edge[i].flow;
			if (dis[v] == dis[u] + 1 && w > 0 && (f = dfs(v, min(a, w))) > 0) {
				edge[i].flow += f;
				edge[i ^ 1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		if (a == 0) {
			dis[u] = -1;
		}
		return flow;
	}
	int MaxFlow(int s, int t) {
		this->s = s;
		this->t = t;
		int flow = 0;
		while (bfs()) {
			memcpy(cur, head, sizeof(head));
			flow += dfs(s, INF);
		}
		return flow;
	}
};

int CountBit(int x) {
	int cnt = 0;
	while (x) {
		cnt++;
		x -= (x & (-x));
	}
	return cnt;
}

Dinic net;
int S, T;
int Less[MAXN], More[MAXN];
int LessId[MAXN], MoreId[MAXN];
int t[MAXN], u[MAXN];

void ReadData(int n, int m) {
	fill_n(Less, n + 3, -1);
	fill_n(More, n + 3, -1);
	for (int i = 0; i < n; ++i) {
		t[i] = nextInt();
	}
	for (int i = 0; i < n; ++i) {
		u[i] = nextInt();
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int w = nextInt();
			w += 1024;
			if (j < t[i]) {
				if (w > Less[i]) {
					Less[i] = w;
					LessId[i] = j;
				}
			} else {
				if (w > More[i]) {
					More[i] = w;
					MoreId[i] = j;
				}
			}
		}
	}
}
void BuildGraph(int n, int m) {
	S = 0, T = n + n + 1;
	net.Init(S + T + 1);
	for (int i = 0; i < n; ++i) {
		int c = CountBit(i);
		if (c & 1) {
			net.AddEdge(S, i + 1, Less[i]);
			net.AddEdge(i + 1 + n, T, More[i]);
		} else {
			net.AddEdge(S, i + 1, More[i]);
			net.AddEdge(i + 1 + n, T, Less[i]);
		}
		net.AddEdge(i + 1, i + 1 + n, INF);
		for (int j = i + 1; j < n; ++j) {
			if (CountBit(i ^ j) == 1) {
				if (c & 1) {
					net.AddEdge(i + 1, j + 1 + n, u[i] ^ u[j]);
				} else {
					net.AddEdge(j + 1, i + 1 + n, u[i] ^ u[j]);
				}
			}
		}
	}
	net.MaxFlow(S, T);
}
void GetSolution(int n, int m) {
	vector<int> ret;
	for (int i = 0; i < n; ++i) {
		int c = CountBit(i);
		if (c & 1) {
			if (net.dis[i + 1] != -1) {
				ret.push_back(LessId[i]);
			} else {
				ret.push_back(MoreId[i]);
			}
		} else {
			if (net.dis[i + 1] != -1) {
				ret.push_back(MoreId[i]);
			} else {
				ret.push_back(LessId[i]);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d%c", ret[i], (i == n - 1) ? '\n' : ' ');
	}
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int C;
	scanf("%d", &C);
	while (C--) {
		int n = nextInt();
		int m = nextInt();
		n = 1 << n;
		m = 1 << m;
		ReadData(n, m);
		BuildGraph(n, m);
		GetSolution(n, m);
	}
	return 0;
}

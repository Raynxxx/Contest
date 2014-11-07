/*
** CF 434D Nanami's Power Plant
** Created by Rayn @@ 2014/10/08
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
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
typedef vector<int>::iterator Pointer;
const int MAXN = 64;
const int INF = 0x3F3F3F3F;

class ISAP {
public:
	const static int NODE = 10010;

	struct Edge {
		int from, to, cap, flow;
		Edge() {}
		Edge(int from, int to, int cap, int flow) :
			from(from), to(to), cap(cap), flow(flow) {}
	};

	int n, m, s, t;
	bool vis[NODE];
	int cur[NODE];
	int pre[NODE];
	int num[NODE];
	int d[NODE];
	vector<Edge> edge;
	vector<int> G[NODE];


	void Init(int n) {
		this->n = n;
		this->m = 0;
		for (int i = 0; i <= n; ++i) {
			G[i].clear();
		}
		edge.clear();
		//edge.reserve(MAXM);
	}
	void AddEdge(int from, int to, int cap) {
		edge.push_back(Edge(from, to, cap, 0));
		edge.push_back(Edge(to, from, 0, 0));
		m = edge.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
	bool bfs() {
		memset(vis, 0, sizeof(vis));
		queue<int> Q;
		Q.push(t);
		vis[t] = true;
		d[t] = 0;
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (Pointer it = G[u].begin(); it != G[u].end(); ++it)
			{
				int v = edge[*it ^ 1].from;
				int w = edge[*it ^ 1].cap - edge[*it ^ 1].flow;
				if (!vis[v] && w > 0)
				{
					vis[v] = true;
					d[v] = d[u] + 1;
					Q.push(v);
				}
			}
		}
		return vis[s];
	}
	int Augment() {
		int x = t, A = INF;
		while (x != s)
		{
			Edge& e = edge[pre[x]];
			A = min(A, e.cap - e.flow);
			x = edge[pre[x]].from;
		}
		x = t;
		while (x != s)
		{
			edge[pre[x]].flow += A;
			edge[pre[x] ^ 1].flow -= A;
			x = edge[pre[x]].from;
		}
		return A;
	}
	LL MaxFlow(int s, int t) {
		this->s = s; this->t = t;
		LL flow = 0;
		bfs();
		memset(num, 0, sizeof(num));
		for (int i = 0; i < n; ++i) {
			num[d[i]]++;
		}
		int u = s;
		memset(cur, 0, sizeof(cur));
		while (d[s] < n)
		{
			if (u == t)
			{
				flow += Augment();
				u = s;
			}
			bool ok = false;
			for (int i = cur[u]; i < (int)G[u].size(); i++)
			{
				Edge& e = edge[G[u][i]];
				if (e.cap > e.flow && d[u] == d[e.to] + 1)
				{
					ok = true;
					pre[e.to] = G[u][i];
					cur[u] = i;
					u = e.to;
					break;
				}
			}
			if (!ok)
			{
				int low = n - 1;
				for (Pointer it = G[u].begin(); it != G[u].end(); ++it)
				{
					Edge& e = edge[*it];
					if (e.cap > e.flow) {
						low = min(low, d[e.to]);
					}
				}
				if (--num[d[u]] == 0) break;
				num[d[u] = low + 1]++;
				cur[u] = 0;
				if (u != s) {
					u = edge[pre[u]].from;
				}
			}
		}
		return flow;
	}
};

ISAP Network;

int a[MAXN], b[MAXN], c[MAXN];
int l[MAXN], r[MAXN];
int S, T, M, dot[MAXN];

int function(int i, int x) {
	return a[i] * x * x + b[i] * x + c[i];
}
int node(int i, int j) {
	return dot[i] + j - l[i];
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			a[i] = nextInt();
			b[i] = nextInt();
			c[i] = nextInt();
		}
		S = 0, T = 1, M = 0;
		for (int i = 1; i <= n; ++i) {
			l[i] = nextInt();
			r[i] = nextInt();
			dot[i] = T;
			T += r[i] - l[i] + 2;
			for (int j = l[i]; j <= r[i]; ++j) {
				M = max(M, function(i, j) + 10);
			}
		}
		Network.Init(S + T + 1);
		for (int i = 1; i <= n; ++i) {
			Network.AddEdge(S, dot[i], INF);
			for (int j = l[i]; j <= r[i]; ++j) {
				Network.AddEdge(node(i, j), node(i, j) + 1, M - function(i, j));
			}
			Network.AddEdge(node(i, r[i]) + 1, T, INF);
		}
		for (int i = 1; i <= m; ++i) {
			int u = nextInt();
			int v = nextInt();
			int d = nextInt();
			for (int j = l[u]; j <= r[u]; ++j) {
				if (j - d >= l[v] && j - d <= r[v] + 1) {
					Network.AddEdge(node(u, j), node(v, j - d), INF);
				}
			}
		}
		outInteger(M * n - Network.MaxFlow(S, T));
		cout << endl;
	}
	return 0;
}

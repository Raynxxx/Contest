/*
** HDU 4871 Shortest-path tree
** Created by Rayn @@ 2014/10/19
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
#include <functional>
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
	inline void newline() {
		putchar('\n');
	}
};

using namespace std;
using namespace FastIO;

typedef long long Long;
typedef pair<int, int> PII;
const int MAXN = 30020;
const int MOD = 10007;
const int INF = 0x3F3F3F3F;

int pre[MAXN], prew[MAXN];
bool vis[MAXN];

class Dijkstra {
public:
	int n;
	bool vis[MAXN];
	int dist[MAXN];
	vector<PII> edges[MAXN];
	typedef vector<PII>::iterator Iter;

	void Init(int n) {
		this->n = n;
		for (int i = 0; i <= n; ++i) {
			edges[i].clear();
		}
	}
	void AddEdge(int u, int v, int w) {
		edges[u].push_back(make_pair(v, w));
		edges[v].push_back(make_pair(u, w));
	}
	void Work(int st) {
		fill_n(dist, n + 3, INF);
		fill_n(vis, n + 3, false);
		priority_queue< PII, vector<PII>, greater<PII> > pq;
		pq.push(make_pair(0, st));
		dist[st] = 0;
		pre[st] = -1;
		while (!pq.empty()) {
			PII cur = pq.top();
			pq.pop();
			int u = cur.second;
			if (vis[u]) continue;
			vis[u] = false;
			for (Iter it = edges[u].begin(); it != edges[u].end(); ++it) {
				int v = it->first;
				int w = it->second;
				if (!vis[v]) {
					if (dist[v] > dist[u] + w) {
						dist[v] = dist[u] + w;
						pre[v] = u;
						prew[v] = w;
						pq.push(make_pair(dist[v], v));
					} else if (dist[v] == dist[u] + w && u < pre[v]) {
						pre[v] = u;
						prew[v] = w;
					}
				}
			}
		}
	}
};

struct Edge {
	int v, w, next;
	Edge() {}
	Edge(int v, int w, int next) : v(v), w(w), next(next) {}
};

Dijkstra dijkstra;
Edge edge[MAXN << 1];
int nedge, head[MAXN];
int path_len, path_cnt;
int minsz, maxdep, sz[MAXN];
int dp[MAXN], dpcnt[MAXN];
int pd[MAXN], pdcnt[MAXN];

void ShortestPath(int n, int m) {
	dijkstra.Init(n);
	for (int i = 0; i < m; ++i) {
		int u = nextInt();
		int v = nextInt();
		int w = nextInt();
		dijkstra.AddEdge(u, v, w);
	}
	dijkstra.Work(1);
}
void AddEdge(int u, int v, int w) {
	edge[nedge] = Edge(v, w, head[u]);
	head[u] = nedge++;
}
void ConstructTree(int n) {
	path_len = path_cnt = 0;
	nedge = 0;
	fill_n(head, n + 3, -1);
	fill_n(vis, n + 3, false);
	for (int i = 2; i <= n; ++i) {
		AddEdge(i, pre[i], prew[i]);
		AddEdge(pre[i], i, prew[i]);
	}
}
int TreeSize(int u, int fa) {
	sz[u] = 1;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == fa || vis[v]) continue;
		sz[u] += TreeSize(v, u);
	}
	return sz[u];
}
void FindRoot(int u, int fa, int totsz, int& root) {
	int maxsz = totsz - sz[u];
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == fa || vis[v]) continue;
		FindRoot(v, u, totsz, root);
		maxsz = max(maxsz, sz[v]);
	}
	if (maxsz < minsz) {
		minsz = maxsz;
		root = u;
	}
}
void GetPD(int u, int fa, int nw, int nd, int k) {
	if (nd > k - 1) return;
	if (maxdep < nd) maxdep = nd;
	if (nw > pd[nd]) {
		pd[nd] = nw;
		pdcnt[nd] = 1;
	} else if (nw == pd[nd]) {
		pdcnt[nd]++;
	}
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (v == fa || vis[v]) continue;
		GetPD(v, u, nw + edge[i].w, nd + 1, k);
	}
}
void DivGao(int u, int k) {
	int totsz = TreeSize(u, -1);
	minsz = INF;
	int root;
	FindRoot(u, -1, totsz, root);
	vis[root] = true;
	fill_n(dp, totsz + 1, 0);
	fill_n(dpcnt, totsz + 1, 0);
	dpcnt[0] = 1;
	for (int i = head[root]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (vis[v]) continue;
		maxdep = 0;
		fill_n(pd, sz[v] + 1, 0);
		fill_n(pdcnt, sz[v] + 1, 0);
		pdcnt[0] = 1;
		GetPD(v, root, edge[i].w, 1, k);
		for (int j = 1; j <= maxdep && j < k; ++j) {
			if (pdcnt[j] && dpcnt[k - j - 1]) {
				if (path_len < pd[j] + dp[k - j - 1]) {
					path_len = pd[j] + dp[k - j - 1];
					path_cnt = pdcnt[j] * dpcnt[k - j - 1];
				} else if (path_len == pd[j] + dp[k - j - 1]) {
					path_cnt += pdcnt[j] * dpcnt[k - j - 1];
				}
			}
		}
		for (int j = 1; j <= maxdep && j <= k; ++j) {
			if (dp[j] < pd[j]) {
				dp[j] = pd[j];
				dpcnt[j] = pdcnt[j];
			} else if (dp[j] == pd[j]) {
				dpcnt[j] += pdcnt[j];
			}
		}
	}
	for (int i = head[root]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (vis[v]) continue;
		DivGao(v, k);
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T = nextInt();
	while (T--) {
		int n = nextInt();
		int m = nextInt();
		int k = nextInt();
		ShortestPath(n, m);
		ConstructTree(n);
		DivGao(1, k);
		printf("%d %d\n", path_len, path_cnt);
	}
	return 0;
}

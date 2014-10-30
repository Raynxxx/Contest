/*
** HDU 4467 Graph
** Created by Rayn @@ 2014/10/03
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

namespace QuickIO {
	/* Input >> int >> long >> long long */
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

	/* Output << int << long << long long */
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
using namespace QuickIO;
typedef long long LL;
const int MAXN = 100005;
const int MAXM = 100005;
const int Limit = 320;

struct Edge {
	int u, v;
	int next;
	long long w;
	Edge() {}
	Edge(int u, int v, long long w) :
		u(u), v(v), w(w), next(0) {}
	Edge(int u, int v, long long w, int next) :
		u(u), v(v), w(w), next(next) {}
	inline bool operator == (const Edge& rhs) const {
		return (u == rhs.u && v == rhs.v);
	}
	inline bool operator < (const Edge& rhs) const {
		return u < rhs.u || (u == rhs.u && v < rhs.v);
	}
};

struct HNode {
	bool tag;
	long long val[2];
};

int sz;
int head[MAXN];
int color[MAXN];
int degree[MAXN];
long long sum[3];
HNode Node[MAXN];
Edge edge[MAXM];
Edge Graph[MAXM << 1];

inline void GraphInit(int n) {
	sz = 0;
	fill_n(sum, 3, 0);
	for (int i = 0; i <= n; ++i) {
		head[i] = -1;
		degree[i] = 0;
		Node[i].tag = false;
		Node[i].val[0] = Node[i].val[1] = 0;
	}
}
inline void AddEdge(int u, int v, long long w) {
	Graph[sz] = Edge(u, v, w, head[u]);
	head[u] = sz++;
}

void Change(int u) {
	if (Node[u].tag) { //HeavyNode
		for (int i = head[u]; i != -1; i = Graph[i].next) {
			int v = Graph[i].v;
			Node[v].val[color[u]] -= Graph[i].w;
			Node[v].val[color[u]^1] += Graph[i].w;
		}
	} else {
		Node[u].val[0] = Node[u].val[1] = 0;
		for (int i = head[u]; i != -1; i = Graph[i].next) {
			int v = Graph[i].v;
			Node[u].val[color[v]] += Graph[i].w;
			if (Node[v].tag) {
				Node[v].val[color[u]] -= Graph[i].w;
				Node[v].val[color[u] ^ 1] += Graph[i].w;
			}
		}
	}
	sum[color[u]] -= Node[u].val[0];
	sum[color[u] + 1] -= Node[u].val[1];
	color[u] ^= 1;
	sum[color[u]] += Node[u].val[0];
	sum[color[u] + 1] += Node[u].val[1];
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m, cases = 0;
	char cmd[20];
	while (scanf("%d%d", &n, &m) != EOF) {
		GraphInit(n);
		for (int i = 1; i <= n; ++i) {
			color[i] = nextInt();
		}
		for (int i = 1; i <= m; ++i) {
			edge[i].u = nextInt();
			edge[i].v = nextInt();
			edge[i].w = nextLong();
			if (edge[i].u > edge[i].v) {
				swap(edge[i].u, edge[i].v);
			}
		}
		sort(edge + 1, edge + 1 + m);
		int cnt = 1;
		for (int i = 2; i <= m; ++i) {
			if (edge[i] == edge[cnt]) {
				edge[cnt].w += edge[i].w;
			} else {
				edge[++cnt] = edge[i];
			}
		}
		m = cnt;
		for (int i = 1; i <= m; ++i) {
			int u = edge[i].u;
			int v = edge[i].v;
			degree[u]++;
			degree[v]++;
			sum[color[u] + color[v]] += edge[i].w;
		}
		for (int i = 1; i <= n; ++i) {
			if (degree[i] >= Limit) {
				Node[i].tag = true;
			}
		}
		for (int i = 1; i <= m; ++i) {
			int u = edge[i].u;
			int v = edge[i].v;
			Node[u].val[color[v]] += edge[i].w;
			Node[v].val[color[u]] += edge[i].w;
			/*
			** << 重点不向轻点连边 >>
			** 对于点x，度数大于点得到了更新；度数小于它的，信息则没有更新
			** 那么，当处理到那些度数小的点时，也是按同样的方法在处理，这不
			** 就是把以前没有更新的过程给完成了吗!
			** 总而言之，就是利用度数形成一种顺序的结构，使其不会混乱。
			*/
			if (Node[u].tag && Node[v].tag) {
				AddEdge(u, v, edge[i].w);
				AddEdge(v, u, edge[i].w);
			}
			if (!Node[u].tag) {
				AddEdge(u, v, edge[i].w);
			}
			if (!Node[v].tag) {
				AddEdge(v, u, edge[i].w);
			}
		}
		int Q = nextInt();
		printf("Case %d:\n", ++cases);
		while (Q--) {
			scanf("%s", cmd);
			if (cmd[0] == 'C') {
				int x = nextInt();
				Change(x);
			} else if (cmd[0] == 'A') {
				int A = nextInt();
				int B = nextInt();
				outInteger(sum[A + B]);
				printf("\n");
			}
		}
	}
	return 0;
}

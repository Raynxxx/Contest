/*
** HDU 3966 Aragorn's Story
** Created by Rayn @@ 2014/10/06
** BIT + 差分 优化, 常数小太多.
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

typedef long long LL;
const int MAXN = 50010;
const int INF = 0x3F3F3F3F;

class BinaryIndexTree {
public:
	int n;
	int tree[MAXN];
	void Init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(tree));
	}
	inline int LowBit(int x) {
		return x & (-x);
	}
	inline void Add(int x, int d) {
		while (x <= n) {
			tree[x] += d;
			x += LowBit(x);
		}
	}
	inline int Sum(int x) {
		int ret = 0;
		while (x > 0) {
			ret += tree[x];
			x ^= LowBit(x);
		}
		return ret;
	}
};
class HeavyLightDecompose {
public:
	struct Edge {
		int to, next;
		Edge() {}
		Edge(int to, int next) : to(to), next(next) {}
	};

	Edge edge[MAXN << 2];
	int tot, head[MAXN];
	int pos, top[MAXN], fa[MAXN], deep[MAXN];
	int num[MAXN], son[MAXN], p[MAXN], fp[MAXN];
	int node_val[MAXN];
	BinaryIndexTree bit;

	void Init()
	{
		tot = pos = 0;
		memset(head, -1, sizeof(head));
		memset(son, -1, sizeof(son));
	}
	void AddEdge(int u, int v)
	{
		edge[tot] = Edge(v, head[u]);
		head[u] = tot++;
	}
	void dfs1(int u, int pre, int d)
	{
		deep[u] = d;
		fa[u] = pre;
		num[u] = 1;
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			if (v != pre) {
				dfs1(v, u, d + 1);
				num[u] += num[v];
				if (son[u] == -1 || num[v] > num[son[u]]) {
					son[u] = v;
				}
			}
		}
	}
	void dfs2(int u, int tp)
	{
		top[u] = tp;
		p[u] = ++pos;
		fp[p[u]] = u;
		if (son[u] == -1) return;
		dfs2(son[u], tp);
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			if (v != son[u] && v != fa[u]) {
				dfs2(v, v);
			}
		}
	}
	void Build(int n) {
		dfs1(1, 0, 0);
		dfs2(1, 1);
		bit.Init(n);
		for (int i = 1; i <= n; ++i) {
			bit.Add(p[i], node_val[i]);
			bit.Add(p[i]+1, -node_val[i]);
		}
	}
	void Change(int u, int v, int c)
	{
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (deep[f1] < deep[f2]) {
				swap(f1, f2);
				swap(u, v);
			}
			bit.Add(p[f1], c);
			bit.Add(p[u]+1, -c);
			u = fa[f1];
			f1 = top[u];
		}
		if (deep[u] > deep[v]) swap(u, v);
		bit.Add(p[u], c);
		bit.Add(p[v]+1, -c);
	}
	int Query(int c) {
		return bit.Sum(p[c]);
	}

};

HeavyLightDecompose hld;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m, p;
	while (scanf("%d%d%d", &n, &m, &p) != EOF) {
		hld.Init();
		for (int i = 1; i <= n; ++i) {
			hld.node_val[i] = nextInt();
		}
		for (int i = 1; i <= m; ++i) {
			int u = nextInt();
			int v = nextInt();
			hld.AddEdge(u, v);
			hld.AddEdge(v, u);
		}
		hld.Build(n);
		while (p--) {
			char op[5];
			scanf("%s", op);
			if (op[0] == 'I') {
				int c1 = nextInt();
				int c2 = nextInt();
				int k = nextInt();
				hld.Change(c1, c2, k);
			} else if (op[0] == 'D') {
				int c1 = nextInt();
				int c2 = nextInt();
				int k = nextInt();
				hld.Change(c1, c2, -k);
			} else if (op[0] == 'Q') {
				int c = nextInt();
				outInteger(hld.Query(c));
				printf("\n");
			}
		}
	}
	return 0;
}

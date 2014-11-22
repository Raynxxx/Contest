/*
** FZU 2082 过路费
** Created by Rayn @@ 2014/10/06
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

#define lson (rt<<1)
#define rson (rt<<1|1)

typedef long long LL;
const int MAXN = 50010;
const int INF = 0x3F3F3F3F;

class SegmentTree {
public:
	struct Node {
		int l, r;
		LL sum;
		inline int Mid() {
			return (l + r) >> 1;
		}
	};
	Node tree[MAXN << 2];

	inline void PushUp(int rt) {
		tree[rt].sum = tree[lson].sum + tree[rson].sum;
	}
	void Build(int rt, int l, int r, int v[], int fp[])
	{
		tree[rt].l = l, tree[rt].r = r;
		if (l == r) {
			tree[rt].sum = v[fp[l]];
			return;
		}
		int mid = (l + r) >> 1;
		Build(lson, l, mid, v, fp);
		Build(rson, mid + 1, r, v, fp);
		PushUp(rt);
	}
	void Modify(int rt, int pos, int c)
	{
		if (tree[rt].l == pos && tree[rt].r == pos) {
			tree[rt].sum = c;
			return;
		}
		int mid = tree[rt].Mid();
		if (pos <= mid)
			Modify(lson, pos, c);
		else
			Modify(rson, pos, c);
		PushUp(rt);
	}
	LL Query(int rt, int x, int y)
	{
		if (x <= tree[rt].l && tree[rt].r <= y) {
			return tree[rt].sum;
		}
		int mid = tree[rt].Mid();
		LL ret = 0;
		if (x <= mid)
			ret += Query(lson, x, y);
		if (mid < y)
			ret += Query(rson, x, y);
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
	int Edge_info[MAXN][3];
	SegmentTree st;

	void Init(int n) {
		tot = pos = 0;
		memset(head, -1, sizeof(head));
		memset(son, -1, sizeof(son));
	}
	void AddEdge(int i, int u, int v, int w) {
		edge[tot] = Edge(v, head[u]);
		head[u] = tot++;
		edge[tot] = Edge(u, head[v]);
		head[v] = tot++;
		Edge_info[i][0] = u;
		Edge_info[i][1] = v;
		Edge_info[i][2] = w;
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
		for (int i = 1; i < n; ++i) {
			int& u = Edge_info[i][0];
			int& v = Edge_info[i][1];
			if (deep[u] > deep[v]) {
				swap(u, v);
			}
			node_val[v] = Edge_info[i][2];
		}
		st.Build(1, 1, n, node_val, fp);
	}
	void Change(int a, int b) {
		int pos = p[Edge_info[a][1]];
		st.Modify(1, pos, b);
	}
	LL Query(int u, int v)
	{
		LL ret = 0;
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (deep[f1] < deep[f2]) {
				swap(f1, f2);
				swap(u, v);
			}
			ret += st.Query(1, p[f1], p[u]);
			u = fa[f1];
			f1 = top[u];
		}
		if (u == v) return ret;
		if (deep[u] > deep[v]) swap(u, v);
		ret += st.Query(1, p[son[u]], p[v]);
		return ret;
	}
};

HeavyLightDecompose hld;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		hld.Init(n);
		for (int i = 1; i < n; ++i) {
			int u = nextInt();
			int v = nextInt();
			int w = nextInt();
			hld.AddEdge(i, u, v, w);
		}
		hld.Build(n);
		while (m--) {
			int op = nextInt();
			if (op == 0) {
				int a = nextInt();
				int b = nextInt();
				hld.Change(a, b);
			} else if (op == 1) {
				int a = nextInt();
				int b = nextInt();
				outInteger(hld.Query(a, b));
				printf("\n");
			}
		}
	}
	return 0;
}

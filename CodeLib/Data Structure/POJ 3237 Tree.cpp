/*
** POJ 3237 Tree
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
const int MAXN = 10010;
const int INF = 0x3F3F3F3F;

class SegmentTree {
public:
	struct SegNode {
		int l, r;
		int maxv;
		int minv;
		int tag;
		inline int Mid() {
			return (l + r) >> 1;
		}
		inline void Init(const int& v) {
			tag = 0;
			maxv = minv = v;
		}
	};

	SegNode tree[MAXN << 2];

	inline void PushUp(int rt) {
		tree[rt].maxv = max(tree[lson].maxv, tree[rson].maxv);
		tree[rt].minv = min(tree[lson].minv, tree[rson].minv);
	}
	inline void PushDown(int rt) {
		if (tree[rt].tag) {
			tree[lson].maxv = -tree[lson].maxv;
			tree[lson].minv = -tree[lson].minv;
			swap(tree[lson].maxv, tree[lson].minv);
			tree[rson].maxv = -tree[rson].maxv;
			tree[rson].minv = -tree[rson].minv;
			swap(tree[rson].maxv, tree[rson].minv);
			tree[lson].tag ^= 1;
			tree[rson].tag ^= 1;
			tree[rt].tag = 0;
		}
	}
	void Build(int rt, int l, int r, int v[], int fp[])
	{
		tree[rt].l = l, tree[rt].r = r;
		tree[rt].tag = 0;
		if (l == r) {
			tree[rt].Init(v[fp[l]]);
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
			tree[rt].Init(c);
			return;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		if (pos <= mid)
			Modify(lson, pos, c);
		else
			Modify(rson, pos, c);
		PushUp(rt);
	}
	void Negate(int rt, int x, int y)
	{
		if (x <= tree[rt].l && tree[rt].r <= y) {
			tree[rt].maxv = -tree[rt].maxv;
			tree[rt].minv = -tree[rt].minv;
			swap(tree[rt].maxv, tree[rt].minv);
			tree[rt].tag ^= 1;
			return;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		if (x <= mid)
			Negate(lson, x, y);
		if (mid < y)
			Negate(rson, x, y);
		PushUp(rt);
	}
	int Query(int rt, int x, int y)
	{
		if (x <= tree[rt].l && tree[rt].r <= y) {
			return tree[rt].maxv;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		int ret = -INF;
		if (x <= mid)
			ret = max(ret, Query(lson, x, y));
		if (mid < y)
			ret = max(ret, Query(rson, x, y));
		PushUp(rt);
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

	Edge edge[MAXN << 1];
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
	void Change(int index, int v) {
		int pos = p[Edge_info[index][1]];
		st.Modify(1, pos, v);
	}
	void Negate(int u, int v) {
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (deep[f1] < deep[f2]) {
				swap(f1, f2);
				swap(u, v);
			}
			st.Negate(1, p[f1], p[u]);
			u = fa[f1];
			f1 = top[u];
		}
		if (u == v) return;
		if (deep[u] > deep[v]) swap(u, v);
		st.Negate(1, p[son[u]], p[v]);
	}
	int QueryMax(int u, int v)
	{
		int ret = -INF;
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (deep[f1] < deep[f2]) {
				swap(f1, f2);
				swap(u, v);
			}
			ret = max(ret, st.Query(1, p[f1], p[u]));
			u = fa[f1];
			f1 = top[u];
		}
		if (u == v) return ret;
		if (deep[u] > deep[v]) swap(u, v);
		return max(ret, st.Query(1, p[son[u]], p[v]));
	}
};

HeavyLightDecompose hld;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T = nextInt();
	while (T--) {
		int n = nextInt();
		hld.Init(n);
		for (int i = 1; i < n; ++i) {
			int u = nextInt();
			int v = nextInt();
			int w = nextInt();
			hld.AddEdge(i, u, v, w);
		}
		hld.Build(n);
		char op[10];
		while (scanf("%s", op) && op[0] != 'D') {
			if (op[0] == 'C') {
				int id = nextInt();
				int v = nextInt();
				hld.Change(id, v);
			} else if (op[0] == 'N') {
				int a = nextInt();
				int b = nextInt();
				hld.Negate(a, b);
			} else if (op[0] == 'Q') {
				int a = nextInt();
				int b = nextInt();
				outInteger(hld.QueryMax(a, b));
				printf("\n");
			}
		}
	}
	return 0;
}

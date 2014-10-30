/*
** HDU 4897 Little Devil I
** Created by Rayn @@ 2014/10/20
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
const int MAXN = 100005;

#define lson (tree[rt].ls)
#define rson (tree[rt].rs)

class SegmentTree {
public:
	struct Node {
		int l, r;
		int ls, rs;
		int sum, tag;
		inline int Mid() {
			return (l + r) >> 1;
		}
	};

	int tot;
	Node tree[MAXN << 2];

	void Init() {
		tot = 0;
	}
	int Build(int l, int r) {
		int rt = tot++;
		tree[rt].l = l, tree[rt].r = r;
		tree[rt].tag = tree[rt].sum = 0;
		if (l + 1 == r) {
			tree[rt].ls = tree[rt].rs = -1;
			return rt;
		}
		int mid = (l + r) >> 1;
		tree[rt].ls = Build(l, mid);
		tree[rt].rs = Build(mid, r);
		return rt;
	}
	inline void PushUp(int rt) {
		tree[rt].sum = tree[lson].sum + tree[rson].sum;
	}
	inline void ReverseSum(int rt) {
		tree[rt].tag ^= 1;
		tree[rt].sum = tree[rt].r - tree[rt].l - tree[rt].sum;
	}
	inline void PushDwon(int rt) {
		if (tree[rt].tag) {
			ReverseSum(lson);
			ReverseSum(rson);
			tree[rt].tag = false;
		}
	}
	void Update(int rt, int l, int r) {
		if (l >= r) return;
		if (l >= tree[rt].r || tree[rt].l >= r) return;
		if (tree[rt].l == l && r == tree[rt].r) {
			ReverseSum(rt);
			return;
		}
		PushDwon(rt);
		int mid = tree[rt].Mid();
		if (r <= mid) {
			Update(lson, l, r);
		} else if (mid <= l) {
			Update(rson, l, r);
		} else {
			Update(lson, l, mid);
			Update(rson, mid, r);
		}
		PushUp(rt);
	}
	int Query(int rt, int l, int r) {
		if (l >= r) return 0;
		if (l >= tree[rt].r || r <= tree[rt].l) return 0;
		if (tree[rt].l == l && r == tree[rt].r) {
			return tree[rt].sum;
		}
		PushDwon(rt);
		int mid = tree[rt].Mid();
		if (r <= mid) {
			return Query(lson, l, r);
		} else if (mid <= l) {
			return Query(rson, l, r);
		} else {
			return Query(lson, l, mid) + Query(rson, mid, r);
		}
		PushUp(rt);
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
	int nedge, head[MAXN];
	bool flag[MAXN], filp[MAXN];
	int tot, tid[MAXN], dep[MAXN], fa[MAXN];
	int top[MAXN], son[MAXN], isbuild[MAXN];
	int heavy[MAXN], light[MAXN];
	SegmentTree ST;

	void Init(int n) {
		ST.Init();
		nedge = 0;
		fill_n(head, n + 5, -1);
	}
	void Build(int n) {
		fill_n(tid, n + 5, -1);
		fill_n(filp, n + 5, false);
		fill_n(flag, n + 5, false);
		fill_n(isbuild, n + 5, false);
		flag[1] = true;
		DfsSize(1);
		Decompose(1, -1, 1, 0, 0);
	}
	void AddEdge(int u, int v) {
		edge[nedge] = Edge(v, head[u]);
		head[u] = nedge++;
	}
	int DfsSize(int u) {
		int sz = 1, maxsz = 0, sid = u;
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			if (flag[v]) continue;
			flag[v] = true;
			int t = DfsSize(v);
			if (t > maxsz) {
				maxsz = t, sid = v;
			}
			sz += t;
		}
		son[u] = sid;
		return sz;
	}
	void Decompose(int u, int f, int tp, int depth, int id) {
		fa[u] = f, top[u] = tp, dep[u] = depth, tid[u] = id;
		if (tid[son[u]] == -1) {
			Decompose(son[u], u, tp, depth + 1, id + 1);
		}
		if (!isbuild[tp]) {
			heavy[tp] = ST.Build(0, id + 1);
			light[tp] = ST.Build(0, id + 1);
			isbuild[tp] = true;
		}
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			if (tid[v] != -1) continue;
			Decompose(v, u, v, depth + 1, 0);
		}
	}

	void FilpHeavy(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				swap(u, v);
			}
			ST.Update(heavy[top[u]], 1, tid[u] + 1);
			u = top[u];
			filp[u] ^= 1;
			u = fa[u];
		}
		if (tid[u] > tid[v]) swap(u, v);
		ST.Update(heavy[top[u]], tid[u] + 1, tid[v] + 1);
	}
	void FilpLight(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				swap(u, v);
			}
			ST.Update(light[top[u]], 0, tid[u] + 1);
			ST.Update(heavy[top[u]], tid[u] + 1, tid[u] + 2);
			u = top[u];
			filp[u] ^= 1;
			u = fa[u];
		}
		if (tid[u] > tid[v]) swap(u, v);
		ST.Update(light[top[u]], tid[u], tid[v] + 1);
		if (u == top[u]) {
			filp[u] ^= 1;
		} else {
			ST.Update(heavy[top[u]], tid[u], tid[u] + 1);
		}
		ST.Update(heavy[top[u]], tid[v] + 1, tid[v] + 2);
	}
	int CalLight(int u) {
		int f = fa[u];
		return filp[u] ^ ST.Query(light[top[f]], tid[f], tid[f] + 1);
	}
	int QueryBlack(int u, int v) {
		int ret = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				swap(u, v);
			}
			ret += ST.Query(heavy[top[u]], 1, tid[u] + 1);
			u = top[u];
			ret += CalLight(u);
			u = fa[u];
		}
		if (tid[u] > tid[v]) swap(u, v);
		ret += ST.Query(heavy[top[u]], tid[u] + 1, tid[v] + 1);
		return ret;
	}
};

HeavyLightDecompose hld;

int main() {
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
			hld.AddEdge(u, v);
			hld.AddEdge(v, u);
		}
		hld.Build(n);
		int Q = nextInt();
		while (Q--) {
			int t = nextInt();
			int u = nextInt();
			int v = nextInt();
			if (t == 1) {
				hld.FilpHeavy(u, v);
			} else if (t == 2) {
				hld.FilpLight(u, v);
			} else {
				outInteger(hld.QueryBlack(u, v));
				newline();
			}
		}
	}
	return 0;
}

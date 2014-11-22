/*
** SPOJ Count on a tree I
** Created by Rayn @@ 2014/10/02
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
using namespace std;

typedef long long LL;

inline int nextInt()
{
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
template <typename T>
inline void write(T x)
{
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}

const int MAXN = 100010;
const int MAXM = 200010;
const int INF = 0x3F3F3F3F;

/*
** Graph create part
*/

vector<int> edge[MAXN];

void GraphInit(int n) {
	fill(edge, edge + n + 1, vector<int>());
}
void AddEdge(int u, int v) {
	edge[u].push_back(v);
	edge[v].push_back(u);
}

/*
** LCA part
*/
class LCAMaker {
public:
	int order;
	int pos[MAXN];
	int index[MAXN << 1];
	int level[MAXN << 1];
	int st[20][MAXN << 1];

	void dfs(int u, int p, int dep) {
		index[order] = u;
		pos[u] = order;
		level[order++] = dep;
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (v == p) continue;
			dfs(v, u, dep + 1);
			index[order] = u;
			level[order++] = dep;
		}
	}
	void MakeST(int n, int a[]) {
		for (int i = 0; i < n; ++i) {
			st[0][i] = i;
		}
		for (int i = 1; (1 << i) <= n; ++i) {
			for (int j = 0; j + (1 << i) <= n; ++j) {
				int p = st[i - 1][j];
				int q = st[i - 1][j + (1 << (i - 1))];
				st[i][j] = (a[p] < a[q] ? p : q);
			}
		}
	}
	int GetRMQ(int l, int r, int a[]) {
		if (l > r) swap(l, r);
		int k = 0, range = r - l + 1;
		for (; (1 << k) <= range; ++k);
		--k;
		int p = st[k][l], q = st[k][r - (1 << k) + 1];
		return (a[p] < a[q]) ? p : q;
	}
	int GetLCA(int l, int r) {
		return index[GetRMQ(pos[l], pos[r], level)];
	}
	void MakeLCA(int root) {
		order = 0;
		dfs(root, 1, 0);
		MakeST(order, level);
	}
};

/*
** data hash part
*/

int n, m;
int hash_size;
int weight[MAXN];
int sorted[MAXN];
int pre[MAXN];
LCAMaker lca;

void InitHash(int n) {
	lca.MakeLCA(1);
	memcpy(sorted, weight, sizeof(weight));
	sort(sorted + 1, sorted + 1 + n);
	hash_size = unique(sorted + 1, sorted + 1 + n) - sorted;
}
int LowerBound(int x) {
	return lower_bound(sorted + 1, sorted + hash_size, x) - sorted;
}

/*
** President Segment Tree part
*/

class SegmentTree {
public:
	struct SegNode {
		int val;
		SegNode *Left, *Right;
		SegNode(int val = 0, SegNode *Left = NULL, SegNode *Right = NULL):
			val(val), Left(Left), Right(Right) {}
		inline void PushUp() {
			val = Left->val + Right->val;
		}
	};

	SegNode pool[MAXN*20];
	SegNode *null;
	SegNode *root[MAXN];
	int tail;

	SegNode* newnode() {
		return &pool[tail++];
	}
	SegNode* Build(int l, int r) {
		SegNode *rt = newnode();
		if (l == r) {
			rt->Left = rt->Right = null;
			return rt;
		}
		int mid = (l + r) >> 1;
		rt->Left = Build(l, mid);
		rt->Right = Build(mid + 1, r);
		return rt;
	}
	SegNode* Insert(SegNode *pre, int l, int r, int p, int v) {
		SegNode *rt = newnode();
		*rt = SegNode(pre->val, pre->Left, pre->Right);
		if (l == r) {
			rt->val += v;
			return rt;
		}
		int mid = (l + r) >> 1;
		if (p <= mid)
			rt->Left = Insert(pre->Left, l, mid, p, v);
		else
			rt->Right = Insert(pre->Right, mid + 1, r, p, v);
		rt->PushUp();
		return rt;
	}
	int Query(SegNode *u, SegNode *v, SegNode *lca, SegNode *lca_fa, int l, int r, int k) {
		if (l == r) {
			return l;
		}
		int mid = (l + r) >> 1;
		int cnt = u->Left->val + v->Left->val - lca->Left->val - lca_fa->Left->val;
		if (k <= cnt)
			return Query(u->Left, v->Left, lca->Left, lca_fa->Left, l, mid, k);
		else
			return Query(u->Right, v->Right, lca->Right, lca_fa->Right, mid + 1, r, k - cnt);
	}
	void Creat() {
		tail = 0;
		null = newnode();
		null->Left = null->Right = null;
		root[0] = Build(1, hash_size);
		Creat(1, 0, root[0]);
	}
	void Creat(int u, int p, SegNode *fa) {
		pre[u] = p;
		root[u] = Insert(fa, 1, hash_size, LowerBound(weight[u]), 1);
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (v == p) continue;
			Creat(v, u, root[u]);
		}
	}
	int Query(int u, int v, int k) {
		int LCA = lca.GetLCA(u, v);
		return Query(root[u], root[v], root[LCA], root[pre[LCA]], 1, hash_size, k);
	}
};

SegmentTree pst;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			weight[i] = nextInt();
		}
		GraphInit(n);
		for (int i = 1; i < n; ++i) {
			int u = nextInt();
			int v = nextInt();
			AddEdge(u, v);
		}
		InitHash(n);
		pst.Creat();
		while (m--) {
			int u = nextInt();
			int v = nextInt();
			int k = nextInt();
			printf("%d\n", sorted[pst.Query(u, v, k)]);
		}
	}
	return 0;
}

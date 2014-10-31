/*
** HDU 4912 Least common multiple
** Created by Rayn @@ 2014/10/31
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

typedef long long Long;
const int MAXN = 100100;
const int MOD = (int)1e9 + 7;
const double EPS = 1e-6;

struct Node {
	int a, b;
	void read() {
		a = nextInt();
		b = nextInt();
	}
	bool operator < (const Node& rhs) const {
		return a < rhs.a || (a == rhs.a && b < rhs.b);
	}
};

Long QucikPow(Long x, int n) {
	Long ret = 1;
	while (n) {
		if (n & 1) ret = (ret * x) % MOD;
		x = (x * x) % MOD;
		n >>= 1;
	}
	return ret;
}

#define lson (rt << 1)
#define rson (rt << 1|1)

class SegmentTree {
public:
	struct SegNode {
		int l, r;
		int sum, mul;
		inline int Mid() {
			return (l + r) >> 1;
		}
	};

	SegNode tree[MAXN << 2];

	void Build(int rt, int l, int r) {
		tree[rt].l = l, tree[rt].r = r;
		tree[rt].sum = 0, tree[rt].mul = 1;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		Build(lson, l, mid);
		Build(rson, mid + 1, r);
	}
	void PushUp(int rt) {
		tree[rt].sum = (tree[lson].sum + tree[rson].sum) % MOD;
	}
	void PushDown(int rt) {
		if (tree[rt].mul > 1) {
			tree[lson].mul = ((Long)tree[lson].mul * tree[rt].mul) % MOD;
			tree[rson].mul = ((Long)tree[rson].mul * tree[rt].mul) % MOD;
			tree[lson].sum = ((Long)tree[lson].sum * tree[rt].mul) % MOD;
			tree[rson].sum = ((Long)tree[rson].sum * tree[rt].mul) % MOD;
			tree[rt].mul = 1;
		}
	}
	void Modify(int rt, int pos, Long val) {
		if (tree[rt].l == tree[rt].r) {
			tree[rt].sum = (val * tree[rt].mul) % MOD;
			return;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		if (pos <= mid)
			Modify(lson, pos, val);
		else
			Modify(rson, pos, val);
		PushUp(rt);
	}
	void Multiply2(int rt, int x, int y) {
		if (x <= tree[rt].l && tree[rt].r <= y) {
			tree[rt].mul = (tree[rt].mul * 2) % MOD;
			tree[rt].sum = (tree[rt].sum * 2) % MOD;
			return;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		if (x <= mid)
			Multiply2(lson, x, y);
		if (mid < y)
			Multiply2(rson, x, y);
		PushUp(rt);
	}
	Long Query(int rt, int x, int y) {
		if (x <= tree[rt].l && tree[rt].r <= y) {
			return tree[rt].sum;
		}
		PushDown(rt);
		int mid = tree[rt].Mid();
		Long ret = 0;
		if (x <= mid)
			ret = (ret + Query(lson, x, y)) % MOD;
		if (mid < y)
			ret = (ret + Query(rson, x, y)) % MOD;
		return ret;
	}
};

SegmentTree seg;
Node var[MAXN];
vector<int> b;

int LowerBound(int tag) {
	int p = lower_bound(b.begin(), b.end(), tag) - b.begin();
	b[p] -= 1;
	return p;
}
void GetRet(int n) {
	seg.Build(1, 0, n);
	Long ret = 0;
	for (int i = 0; i < n; ++i) {
		Long cur = QucikPow(2, var[i].a);
		int pos = LowerBound(var[i].b);
		seg.Modify(1, pos, QucikPow(3, var[i].b));
		ret = (ret + (cur * seg.Query(1, pos, n)) % MOD) % MOD;
		seg.Multiply2(1, pos + 1, n);
	}
	printf("%I64d\n", ret);
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n;
	while (scanf("%d", &n) != EOF) {
		b.resize(n, 0);
		for (int i = 0; i < n; ++i) {
			var[i].read();
			b[i] = var[i].b;
		}
		sort(var, var + n);
		sort(b.begin(), b.end());
		GetRet(n);
	}
	return 0;
}

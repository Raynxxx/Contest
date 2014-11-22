/*
** LA 6667 Longest Chain
** Created by Rayn @@ 2014/10/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN = 300050;

void Update(int& x, int y) {
	x = max(x, y);
}
class BinaryIndexedTree {
public:
	int n;
	int tree[MAXN];
	void Init(int n) {
		this->n = n;
		fill_n(tree, n + 10, 0);
	}
	inline int Lowbit(int x) {
		return x & (-x);
	}
	void Add(int idx, int val) {
		while (idx <= n) {
			Update(tree[idx], val);
			idx += Lowbit(idx);
		}
	}
	int Sum(int idx) {
		int ret = 0;
		while (idx > 0) {
			Update(ret, tree[idx]);
			idx -= Lowbit(idx);
		}
		return ret;
	}
	void Clear(int idx) {
		while (idx <= n) {
			tree[idx] = 0;
			idx += Lowbit(idx);
		}
	}
};

struct Point {
	int x, y, z;
	int id;
	Point() {}
	Point(int x, int y, int z, int id = 0) : x(x), y(y), z(z), id(id) {}
	bool operator < (const Point& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		if (y != rhs.y) return y < rhs.y;
		return z < rhs.z;
	}
};

bool cmpRank(const Point& A, const Point& B) {
	if (A.y != B.y) return A.y < B.y;
	return A.z > B.z;
}
BinaryIndexedTree bit1, bit2;
Point orgin[MAXN], pt[MAXN];
int n, m, A, B;
int setz[MAXN], dp[MAXN];

const int C = ~(1 << 31);
const int M = (1 << 16) - 1;

void Init(int n) {
	bit1.Init(n);
	bit2.Init(n);
	fill_n(dp, n + 2, 1);
}
int Generate(int& a, int& b) {
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}
void cdq_Gao(int l, int mid, int r) {
	int sz = 0;
	for (int i = l; i <= r; ++i) {
		pt[sz] = orgin[i];
		pt[sz++].x = 0;
	}
	int MidX = orgin[mid + 1].x;
	sort(pt, pt + sz, cmpRank);
	for (int i = 0; i < sz; ++i) {
		if (pt[i].id <= mid) {
			bit1.Add(pt[i].z, dp[pt[i].id]);
			if (orgin[pt[i].id].x != MidX) {
				bit2.Add(pt[i].z, dp[pt[i].id]);
			}
		}
		else {
			if (orgin[pt[i].id].x != MidX) {
				int t = bit1.Sum(pt[i].z - 1);
				Update(dp[pt[i].id], t + 1);
			}
			else {
				int t = bit2.Sum(pt[i].z - 1);
				Update(dp[pt[i].id], t + 1);
			}
		}
	}
	for (int i = 0; i < sz; ++i) {
		if (pt[i].id <= mid) {
			bit1.Clear(pt[i].z);
			bit2.Clear(pt[i].z);
		}
	}
}
void cdq_Merge(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq_Merge(l, mid);
	cdq_Gao(l, mid, r);
	cdq_Merge(mid + 1, r);
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d%d%d", &n, &m, &A, &B) != EOF && (n + m + A + B)) {
		Init(n + m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &orgin[i].x, &orgin[i].y, &orgin[i].z);
			setz[i] = orgin[i].z;
		}
		for (int i = n + 1; i <= n + m; ++i) {
			orgin[i].x = Generate(A, B);
			orgin[i].y = Generate(A, B);
			orgin[i].z = Generate(A, B);
			setz[i] = orgin[i].z;
		}
		n += m;
		sort(orgin + 1, orgin + 1 + n);
		sort(setz + 1, setz + 1 + n);
		int cntz = unique(setz + 1, setz + 1 + n) - (setz + 1);
		for (int i = 1; i <= n; ++i) {
			orgin[i].z = lower_bound(setz + 1, setz + 1 + cntz, orgin[i].z) - setz;
			orgin[i].id = i;
		}
		cdq_Merge(1, n);
		int ret = 0;
		for (int i = 1; i <= n; ++i) {
			Update(ret, dp[i]);
		}
		printf("%d\n", ret);
	}
	return 0;
}

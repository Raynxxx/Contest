/*
** ZOJ 3525 Disappearance
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
#define lson (rt<<1)
#define rson (rt<<1|1)

typedef long long LL;
const int MAXN = 1010;
const int MAXL = 4010;

class SegmentTree {
public:
	struct SegNode {
		int l, r;
		int maxv;
		int tag;
		inline int Mid() {
			return (l + r) >> 1;
		}
		inline int Length() {
			return (r - l + 1) >> 1;
		}
	};

	SegNode T[MAXL << 2];

	inline void PushUp(int rt) {
		T[rt].maxv = max(T[lson].maxv, T[rson].maxv);
	}
	inline void PushDown(int rt) {
		if (T[rt].tag) {
			T[lson].tag += T[rt].tag;
			T[rson].tag += T[rt].tag;
			T[lson].maxv += T[rt].tag;
			T[rson].maxv += T[rt].tag;
			T[rt].tag = 0;
		}
	}
	void Build(int rt, int l, int r) {
		T[rt].l = l, T[rt].r = r;
		T[rt].maxv = T[rt].tag = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		Build(lson, l, mid);
		Build(rson, mid + 1, r);
	}
	void Update(int rt, int x, int y, int v) {
		if (x <= T[rt].l && T[rt].r <= y) {
			T[rt].tag += v;
			T[rt].maxv += v;
			return;
		}
		PushDown(rt);
		int mid = T[rt].Mid();
		if (x <= mid)
			Update(lson, x, y, v);
		if (mid < y)
			Update(rson, x, y, v);
		PushUp(rt);
	}
	int QueryMax() {
		return T[1].maxv;
	}
};

class Point {
public:
	int x, y, z, s;
	Point() {}
	Point(int x, int y, int z, int s) :
		x(x), y(y), z(z), s(s) {}
	bool operator < (const Point& rhs) const {
		return x < rhs.x;
	}
};

class ScanLine {
public:
	int x, y1, y2, s;
	ScanLine() {}
	ScanLine(int x, int y1, int y2, int s) :
		x(x), y1(y1), y2(y2), s(s) {}
	bool operator < (const ScanLine& rhs) const {
		return x < rhs.x || (x == rhs.x && s > rhs.s);
	}
};


SegmentTree st;
vector<Point> girl;
vector<ScanLine> line;
int LB, LW, LH;

int Gao(int s, int e) {
	line.clear();
	for (int i = s; i <= e; ++i) {
		int x = girl[i].y;
		int y = girl[i].z;
		int s = girl[i].s;
		line.push_back(ScanLine(x, y, y + LH, s));
		line.push_back(ScanLine(x + LW, y, y + LH, -s));
	}
	sort(line.begin(), line.end());
	st.Build(1, 1, MAXL);
	int n = line.size();
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		st.Update(1, line[i].y1, line[i].y2, line[i].s);
		ret = max(ret, st.QueryMax());
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n;
	while (scanf("%d", &n) != EOF) {
		girl.clear();
		for (int i = 0; i < n; ++i) {
			int x, y, z, s;
			scanf("%d%d%d%d", &x, &y, &z, &s);
			if (s < 0) {
				girl.push_back(Point(x + 1000, y + 1000, z + 1000, -s));
			}
		}
		scanf("%d%d%d", &LB, &LW, &LH);
		if (girl.size() == 0) {
			printf("Error 404, mahou shoujo not found!\n");
			continue;
		}
		int range = girl.size();
		sort(girl.begin(), girl.end());
		int ret = -1, left = 0, right = 0;
		while (left < range) {
			while (right < range && girl[right].x - girl[left].x <= LB) {
				right++;
			}
			ret = max(ret, Gao(left, right-1));
			while (left + 1 < range && girl[left + 1].x == girl[left].x) {
				left++;
			}
			left++;
		}
		printf("%d\n", -ret);
	}
	return 0;
}

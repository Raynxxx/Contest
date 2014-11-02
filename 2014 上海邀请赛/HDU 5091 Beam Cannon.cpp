/*
** HDU 5091 Beam Cannon
** Created by Rayn @@ 2014/11/02
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

typedef long long Long;
const int MAXN = 10010;
const int MAXL = 40001;
const int Blance = 20001;

#define lson (rt << 1)
#define rson (rt << 1|1)

struct ScanLine {
	int x, y1, y2;
	int flag;
	ScanLine() {}
	ScanLine(int x, int y1, int y2, int flag) :
		x(x), y1(y1), y2(y2), flag(flag) {}
	bool operator < (const ScanLine& rhs) const {
		return x < rhs.x || (x == rhs.x && flag > rhs.flag);
	}
};

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

SegmentTree st;
ScanLine line[MAXN << 1];
int LineCnt;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, W, H;
	while (scanf("%d", &n) != EOF && n > 0) {
		scanf("%d%d", &W, &H);
		LineCnt = 0;
		for (int i = 0; i < n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			x += Blance, y += Blance;
			line[LineCnt++] = ScanLine(x, y, min(MAXL, y + H), 1);
			line[LineCnt++] = ScanLine(x + W, y, min(MAXL, y + H), -1);
		}
		sort(line, line + LineCnt);
		st.Build(1, 1, MAXL);
		int ret = 0;
		for (int i = 0; i < LineCnt; ++i) {
			int l = line[i].y1, r = line[i].y2;
			st.Update(1, l, r, line[i].flag);
			ret = max(ret, st.QueryMax());
		}
		printf("%d\n", ret);
	}
	return 0;
}

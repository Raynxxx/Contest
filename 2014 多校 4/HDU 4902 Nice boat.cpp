/*
** HDU 4902 Nice boat
** Created by Rayn @@ 2014/10/19
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
typedef pair<int, int> PII;
const int MAXN = 100050;

#define lson (rt << 1)
#define rson (rt << 1|1)

inline int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}
class SegmentTree {
public:
	int maxv[MAXN << 2];
	bool same[MAXN << 2];

	void PushUp(int rt) {
		maxv[rt] = max(maxv[lson], maxv[rson]);
		if (same[lson] && same[rson] && maxv[lson] == maxv[rson])
			same[rt] = true;
		else
			same[rt] = false;
	}
	void PushDown(int rt) {
		if (same[rt]) {
			same[lson] = same[rson] = true;
			maxv[lson] = maxv[rson] = maxv[rt];
		}
	}
	void Build(int rt, int l, int r, int a[]) {
		//same[rt] = false;
		if (l == r) {
			maxv[rt] = a[l];
			same[rt] = true;
			return;
		}
		int mid = (l + r) >> 1;
		Build(lson, l, mid, a);
		Build(rson, mid + 1, r, a);
		PushUp(rt);
	}
	void ModifySame(int rt, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			maxv[rt] = val;
			same[rt] = true;
			return;
		}
		PushDown(rt);
		int mid = (l + r) >> 1;
		if (x <= mid)
			ModifySame(lson, l, mid, x, y, val);
		if (mid < y)
			ModifySame(rson, mid + 1, r, x, y, val);
		PushUp(rt);
	}
	void ModifyGCD(int rt, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			if (maxv[rt] <= val) return;
			if (same[rt]) {
				maxv[rt] = gcd(maxv[rt], val);
			} else {
				int mid = (l + r) >> 1;
				PushDown(rt);
				ModifyGCD(lson, l, mid, x, y, val);
				ModifyGCD(rson, mid + 1, r, x, y, val);
				PushUp(rt);
			}
			return;
		}
		PushDown(rt);
		int mid = (l + r) >> 1;
		if (x <= mid)
			ModifyGCD(lson, l, mid, x, y, val);
		if (mid < y)
			ModifyGCD(rson, mid + 1, r, x, y, val);
		PushUp(rt);
	}
	void Query(int rt, int l, int r, int a[]) {
		if (l == r) {
			a[l] = maxv[rt];
			return;
		}
		PushDown(rt);
		int mid = (l + r) >> 1;
		Query(lson, l, mid, a);
		Query(rson, mid + 1, r, a);
		PushUp(rt);
	}
};


SegmentTree st;
int a[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T = nextInt();
	while (T--) {
		int n = nextInt();
		for (int i = 1; i <= n; ++i) {
			a[i] = nextInt();
		}
		st.Build(1, 1, n, a);
		int Q = nextInt();
		while (Q--) {
			int op = nextInt();
			int l = nextInt();
			int r = nextInt();
			int x = nextInt();
			if (op == 1) {
				st.ModifySame(1, 1, n, l, r, x);
			} else {
				st.ModifyGCD(1, 1, n, l, r, x);
			}
		}
		st.Query(1, 1, n, a);
		for (int i = 1; i <= n; ++i) {
			outInteger(a[i]);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

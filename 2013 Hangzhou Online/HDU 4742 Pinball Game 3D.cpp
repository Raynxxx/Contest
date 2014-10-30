/*
** HDU 4742 Pinball Game 3D
** Created by Rayn @@ 2014/10/11
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
typedef pair<int, int> PII;
const int MAXN = 100010;

struct Point3D {
	int x, y, z, id;
	void read() {
		x = nextInt();
		y = nextInt();
		z = nextInt();
	}
	bool operator < (const Point3D& p) const {
		if (x != p.x) {
			return x < p.x;
		} else if (y != p.y) {
			return y < p.y;
		} else {
			return z < p.z;
		}
	}
};

void Update(PII& res, PII val) {
	if (val.first > res.first) {
		res = val;
	} else if (val.first == res.first) {
		res.second += val.second;
	}
}
class BinaryIndexedTree {
public:
	int n;
	PII tree[MAXN];
	void Init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(PII) * (n+1));
	}
	inline int LowBit(int x) {
		return x & (-x);
	}
	void Add(int idx, PII val) {
		while (idx <= n) {
			Update(tree[idx], val);
			idx += LowBit(idx);
		}
	}
	void Clear(int idx) {
		PII zero = make_pair(0, 0);
		while (idx <= n) {
			tree[idx] = zero;
			idx += LowBit(idx);
		}
	}
	PII Query(int idx) {
		PII ret = make_pair(0, 0);
		while (idx > 0) {
			Update(ret, tree[idx]);
			idx -= LowBit(idx);
		}
		return ret;
	}
};

BinaryIndexedTree bit;
Point3D ball[MAXN];
Point3D pt[MAXN];
vector<int> dz;
pair<int, int> dp[MAXN];

inline void Init(int n) {
	bit.Init(n);
	dz.clear();
	for (int i = 0; i < n; ++i) {
		dp[i] = make_pair(1, 1);
	}
}
void MakeHash(int n) {
	sort(dz.begin(), dz.end());
	dz.erase(unique(dz.begin(), dz.end()), dz.end());
	for (int i = 0; i < n; ++i) {
		ball[i].z = lower_bound(dz.begin(), dz.end(), ball[i].z) - dz.begin() + 1;
	}
	sort(ball, ball + n);
	for (int i = 0; i < n; ++i) {
		ball[i].id = i;
	}
}
void cdq_Gao(int l, int mid, int r) {
	int cnt = 0;
	for (int i = l; i <= r; ++i) {
		pt[cnt] = ball[i];
		pt[cnt++].x = 0;
	}
	sort(pt, pt + cnt);
	for (int i = 0; i < cnt; ++i) {
		if (pt[i].id <= mid) {
			bit.Add(pt[i].z, dp[pt[i].id]);
		} else {
			PII res = bit.Query(pt[i].z);
			res.first += 1;
			Update(dp[pt[i].id], res);
		}
	}
	for (int i = 0; i < cnt; ++i) {
		if (pt[i].id <= mid) {
			bit.Clear(pt[i].z);
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
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	T = nextInt();
	while (T--) {
		int n = nextInt();
		Init(n);
		for (int i = 0; i < n; ++i) {
			ball[i].read();
			dz.push_back(ball[i].z);
		}
		MakeHash(n);
		cdq_Merge(0, n - 1);
		PII res = make_pair(0, 0);
		for (int i = 0; i < n; ++i) {
			Update(res, dp[i]);
		}
		printf("%d %d\n", res.first, res.second);
	}
	return 0;
}

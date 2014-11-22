/*
** ZOJ 3521 Fairy Wars
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

namespace FastIO {
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
}

using namespace std;
using namespace FastIO;
typedef long long LL;

class Point {
public:
	LL x, y;
	Point() {};
	Point(LL x, LL y) : x(x), y(y) {}
	inline void read() {
		x = nextLong();
		y = nextLong();
	}
	inline bool operator < (const Point& rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	friend long long Distance2(const Point& A, const Point& B) {
		return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
	}
};

class DisjointSet {
public:
	vector<int> pa;
	vector<int> sz;
	void Init(int n = 0) {
		pa.resize(n + 1);
		sz.resize(n + 1);
		for (int i = 0; i <= n; ++i) {
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int Find(int x) {
		if (x != pa[x])
			pa[x] = Find(pa[x]);
		return pa[x];
	}
	void Union(int x, int y) {
		int px = Find(x);
		int py = Find(y);
		if (px == py) return;
		if (sz[px] > sz[py]) {
			pa[py] = px;
			sz[px] += sz[py];
		} else {
			pa[px] = py;
			sz[py] += sz[px];
		}
	}
};

const int MAXN = 50000 + 10;
typedef pair<LL, int> PLLI;
typedef set<PLLI>::iterator Pointer;

DisjointSet us;
Point bullet[MAXN];
Point Cirno;
bool frozen[MAXN];

void Init(int n, long long& L) {
	us.Init(n);
	L /= 2;
	fill(frozen, frozen + n + 1, false);
}
long long LL_abs(long long x) {
	return x < 0 ? -x : x;
}
void Gao(int n, long long l, Point que[]) {
	set<PLLI> Solver;
	int top = 1;
	for (int i = 1; i <= n; ++i) {
		while (LL_abs(que[i].x - que[top].x) > l) {
			Solver.erase(make_pair(que[top].y, top));
			top++;
		}
		Pointer pos = Solver.insert(make_pair(que[i].y, i)).first;
		if (pos != Solver.begin()) {
			pos--;
			if (LL_abs(que[i].y - (pos->first)) <= l) {
				us.Union(i, pos->second);
			}
			pos++;
		}
		pos++;
		if (pos != Solver.end() && LL_abs(que[i].y - (pos->first)) <= l) {
			us.Union(i, pos->second);
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int N;
	long long R, L;
	while (scanf("%d %lld %lld", &N, &R, &L) != EOF) {
		for (int i = 1; i <= N; ++i) {
			bullet[i].read();
		}
		Cirno.read();

		Init(N, L);
		sort(bullet + 1, bullet + 1 + N);
		Gao(N, L, bullet);

		int ret = 0;
		for (int i = 1; i <= N; ++i) {
			if (Distance2(bullet[i], Cirno) <= R * R) {
				int pa = us.Find(i);
				if (!frozen[pa]) {
					ret += us.sz[pa];
					frozen[pa] = true;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

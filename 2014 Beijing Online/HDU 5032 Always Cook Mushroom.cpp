/*
** HDU 5032 Always Cook Mushroom
** Created by Rayn @@ 2014/10/06
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

namespace FastIO {
	/* Input >> int >> long >> long long */
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

	/* Output << int << long << long long */
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
typedef vector<PII>::iterator Pointer;

const int MAXN = 1005;
const int MAXM = 100005;

class BinaryIndexTree {
public:
	int n;
	LL tree[MAXN];
	void Init() {
		this->n = 1000;
		memset(tree, 0, sizeof(tree));
	}
	inline int LowBit(int x) {
		return x & (-x);
	}
	inline void Add(int x, int d) {
		while (x <= n) {
			tree[x] += d;
			x += LowBit(x);
		}
	}
	inline LL Sum(int x) {
		LL ret = 0;
		while (x > 0) {
			ret += tree[x];
			x ^= LowBit(x);
		}
		return ret;
	}
};

inline bool Compare(const PII& A, const PII& B) {
	return A.second * B.first < A.first * B.second;
}

struct Query {
	PII pt;
	int x;
	int id;
	inline void read(int id) {
		pt.first = nextInt();
		pt.second = nextInt();
		x = nextInt();
		this->id = id;
	}
	inline bool operator < (const Query& rhs) const {
		return Compare(pt, rhs.pt);
	}
};

BinaryIndexTree bit;
vector<PII> grid;
vector<Query> que;
vector<LL> ret;

void InitGrid(vector<PII>& grid) {
	grid.clear();
	for (int i = 1; i <= 1000; ++i) {
		for (int j = 1; j <= 1000; ++j) {
			grid.push_back(make_pair(i, j));
		}
	}
	sort(grid.begin(), grid.end(), Compare);
}
void Gao(int A, int B, int M) {
	bit.Init();
	int pit = 0;
	for (Pointer it = grid.begin(); it != grid.end(); ++it) {
		while (pit < M && Compare(que[pit].pt, *it)) {
			ret[que[pit].id] = bit.Sum(que[pit].x);
			++pit;
		}
		bit.Add(it->first, (LL)(it->first + A) * (it->second + B));
	}
	while (pit < M) {
		ret[que[pit].id] = bit.Sum(que[pit].x);
		++pit;
	}
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	InitGrid(grid);
	int T = nextInt();
	int cases = 0;
	while (T--) {
		int A = nextInt();
		int B = nextInt();
		int M = nextInt();
		que.resize(M); ret.resize(M);
		for (int i = 0; i < M; ++i) {
			que[i].read(i);
		}
		sort(que.begin(), que.end());

		Gao(A, B, M);

		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < M; ++i) {
			outInteger(ret[i]);
			printf("\n");
		}
	}
	return 0;
}

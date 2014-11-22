/*
** HDU 4417 Super Mario
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
const int MAXN = 100050;

class BinaryIndexedTree {
public:
	int n;
	int tree[MAXN];
	void Init(int n) {
		this->n = n;
		fill_n(tree, n + 10, 0);
	}
	inline int LowBit(int x) {
		return x & (-x);
	}
	void Add(int idx, int v) {
		while (idx <= n) {
			tree[idx] += v;
			idx += LowBit(idx);
		}
	}
	int Sum(int idx) {
		int sum = 0;
		while (idx > 0) {
			sum += tree[idx];
			idx -= LowBit(idx);
		}
		return sum;
	}
};

class QueryNode {
public:
	int l, r, h;
	int id;
	QueryNode() {}
	QueryNode(int l, int r, int h, int id) :
		l(l), r(r), h(h), id(id) {}
	bool operator < (const QueryNode& rhs) const {
		return h < rhs.h;
	}
};

BinaryIndexedTree bit;
QueryNode query[MAXN];
PII brick[MAXN];
int res[MAXN];

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	T = nextInt();
	while (T--) {
		int n = nextInt();
		int m = nextInt();
		for (int i = 0; i < n; ++i) {
			brick[i].first = nextInt();
			brick[i].second = i + 1;
		}
		for (int i = 0; i < m; ++i) {
			int L = nextInt() + 1;
			int R = nextInt() + 1;
			int H = nextInt();
			query[i] = QueryNode(L, R, H, i);
		}
		sort(query, query + m);
		sort(brick, brick + n);
		bit.Init(n);
		for (int i = 0, j = 0; j < m; j++) {
			while (i < n && brick[i].first <= query[j].h) {
				bit.Add(brick[i].second, 1);
				++i;
			}
			res[query[j].id] = bit.Sum(query[j].r) - bit.Sum(query[j].l - 1);
		}
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < m; ++i) {
			outInteger(res[i]);
			putchar('\n');
		}
	}
	return 0;
}

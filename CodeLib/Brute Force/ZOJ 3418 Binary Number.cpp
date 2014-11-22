/*
** ZOJ 3418 Binary Number
** Created by Rayn @@ 2014/10/10
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
const int MAXN = 128;
const int INF = 0x3F3F3F3F;

int a[MAXN];

int CountBit(int a, int b) {
	int f = 0;
	while (a + b) {
		if (a % 2 != b % 2) f++;
		a /= 2;
		b /= 2;
	}
	return f;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T = nextInt();
	while (T--) {
		int m = nextInt();
		int n = nextInt();
		for (int i = 0; i < m; ++i) {
			a[i] = nextInt();
		}
		for (int i = 0; i < n; ++i) {
			int b = nextInt();
			int pos = 0, ret = INF;
			for (int i = 0; i < m; ++i) {
				int f = CountBit(b, a[i]);
				if (f < ret || (f == ret && a[pos] > a[i])) {
					ret = f;
					pos = i;
				}
			}
			outInteger(a[pos]);
			putchar('\n');
		}
	}
	return 0;
}

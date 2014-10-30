/*
** ACdream 1420 High Speed Trains
** Created by Rayn @@ 2014/10/28
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
typedef long long Long;
const int MAXN = 105;

class BigInt {
private:
	const static int MAXSIZE = 510;
	const static int MAXD = 9999;
	const static int DLEN = 4;
public:
	int a[MAXSIZE];
	int length;

	//construst method
	BigInt() {
		memset(a, 0, sizeof(a));
		length = 1;
	}
	BigInt(const int& x) {
		int tmp = x;
		memset(a, 0, sizeof(a));
		length = 0;
		while (tmp > MAXD) {
			int v = tmp - (tmp / (MAXD + 1)) * (MAXD + 1);
			tmp = tmp / (MAXD + 1);
			a[length++] = v;
		}
		a[length++] = tmp;
	}
	BigInt(const char* str) {
		memset(a, 0, sizeof(a));
		length = 0;
		int L = strlen(str);
		for (int i = L - 1; i >= 0; i -= DLEN) {
			int tmp = 0;
			for (int j = max(i - DLEN + 1, 0); j <= i; ++j) {
				tmp = tmp * 10 + (str[j] - '0');
			}
			a[length++] = tmp;
		}
	}
	BigInt(const BigInt& bigx) : length(bigx.length) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < length; ++i) {
			a[i] = bigx.a[i];
		}
	}
	BigInt& operator = (const BigInt& bigx) {
		length = bigx.length;
		memset(a, 0, sizeof(a));
		for (int i = 0; i < length; ++i) {
			a[i] = bigx.a[i];
		}
		return *this;
	}

	//cal method
	BigInt operator + (const BigInt& rhs) const {
		BigInt ret(*this);
		ret.length = max(length, rhs.length);
		for (int i = 0; i < ret.length; ++i) {
			ret.a[i] += rhs.a[i];
			if (ret.a[i] > MAXD) {
				++ret.a[i + 1];
				ret.a[i] -= (MAXD + 1);
			}
		}
		if (ret.a[ret.length] != 0) {
			ret.length++;
		}
		return ret;
	}
	BigInt operator - (const BigInt& rhs) const {
		BigInt t1, t2;
		bool flag;
		if (rhs < *this) {
			t1 = *this, t2 = rhs;
			flag = 0;
		}
		else {
			t1 = rhs, t2 = *this;
			flag = 1;
		}
		int big = t1.length;
		for (int i = 0, j = 0; i < big; ++i) {
			if (t1.a[i] < t2.a[i]) {
				j = i + 1;
				while (t1.a[j] == 0) j++;
				t1.a[j--]--;
				while (j > i) t1.a[j--] += MAXD;
				t1.a[i] += (MAXD + 1) - t2.a[i];
			}
			else {
				t1.a[i] -= t2.a[i];
			}
		}
		t1.length = big;
		while (t1.a[length - 1] == 0 && t1.length > 1) {
			--t1.length;
			--big;
		}
		if (flag) t1.a[big - 1] = 0 - t1.a[big - 1];
		return t1;
	}
	BigInt operator * (const BigInt& rhs) const {
		BigInt ret;
		int t1, t2;
		for (int i = 0; i < length; ++i) {
			int up = 0;
			for (int j = 0; j < rhs.length; ++j) {
				t1 = a[i] * rhs.a[j] + ret.a[i + j] + up;
				if (t1 > MAXD) {
					t2 = t1 - t1 / (MAXD + 1) * (MAXD + 1);
					up = t1 / (MAXD + 1);
					ret.a[i + j] = t2;
				}
				else {
					up = 0;
					ret.a[i + j] = t1;
				}
			}
			if (up != 0) {
				ret.a[i + rhs.length] = up;
			}
		}
		ret.length = length + rhs.length;
		while (ret.a[ret.length - 1] == 0 && ret.length > 1) {
			--ret.length;
		}
		return ret;
	}
	BigInt operator + (const int& rhs) const {
		BigInt B(rhs);
		return (*this) + B;
	}
	BigInt operator - (const int& rhs) const {
		BigInt B(rhs);
		return (*this) - B;
	}
	BigInt operator * (const int& rhs) const {
		BigInt B(rhs);
		return (*this) * B;
	}
	BigInt operator ^ (const int& n) const {
		BigInt t, ret(1);
		if (n < 0) exit(-1);
		if (n == 0) return ret;
		if (n == 1) return *this;
		int i, m = n;
		while (m > 1) {
			t = *this;
			for (i = 1; (i << 1) <= m; i <<= 1) {
				t = t * t;
			}
			m -= i;
			ret = ret * t;
			if (m == 1) ret = ret * (*this);
		}
		return ret;
	}

	//compare method
	bool operator < (const BigInt& rhs) const {
		if (length != rhs.length) {
			return length < rhs.length;
		}
		else {
			int i = length - 1;
			while (a[i] == rhs.a[i] && i >= 0) {
				i--;
			}
			if (i >= 0 && a[i] != rhs.a[i]) {
				return a[i] < rhs.a[i];
			}
			return true;
		}
	}
	bool operator < (const int& rhs) const {
		BigInt t(rhs);
		return *this < t;
	}

	inline void print() {
		printf("%d", a[length - 1]);
		for (int i = length - 2; i >= 0; --i) {
			printf("%04d", a[i]);
		}
	}
	inline void println() {
		this->print();
		putchar('\n');
	}
	string toString() {
		string ret;
		for (int i = length - 1; i >= 0; --i) {
			if (i != length - 1) {
				if (a[i] < 1000) ret += '0';
				if (a[i] < 100) ret += '0';
				if (a[i] < 10) ret += '0';
			}
			string tmp;
			int n = a[i];
			do {
				char c = n % 10 + '0';
				tmp = c + tmp;
				n /= 10;
			} while (n);
			ret += tmp;
		}
		return ret;
	}
};

BigInt comb[MAXN][MAXN];
BigInt dp[MAXN];

void comb_table() {
	comb[0][0] = BigInt(1);
	for (int i = 1; i <= 100; ++i) {
		comb[i][0] = comb[i][i] = BigInt(1);
		for (int j = 1; j < i; ++j) {
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
		}
	}
}
void Gao(int n) {
	comb_table();
	dp[0] = BigInt(1);
	dp[1] = BigInt(0);
	for (int i = 2; i <= n; ++i) {
		dp[i] = BigInt(2) ^ (i * (i - 1) / 2);
		for (int j = 1; j <= i; ++j) {
			dp[i] = dp[i] - comb[i][j] * dp[i - j];
		}
	}
}
int main() {
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	Gao(100);
	int n;
	while (scanf("%d", &n) != EOF) {
		dp[n].println();
	}
	return 0;
}

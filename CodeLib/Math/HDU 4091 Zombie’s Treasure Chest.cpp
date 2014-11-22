/*
** HDU 4091 Zombie’s Treasure Chest
** Created by Rayn @@ 2014/10/07
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
const int MAXN = 10010;
const int INF = 0x3F3F3F3F;

LL GCD(LL a, LL b) {
	return (b == 0) ? a : GCD(b, a%b);
}
LL LCM(LL a, LL b) {
	return a / GCD(a, b) * b;
}
int main()
{
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	int T = nextInt();
	int cases = 0;
	long long N, S1, V1, S2, V2;
	while (T--) {
		N = nextLong();
		S1 = nextLong(), V1 = nextLong();
		S2 = nextLong(), V2 = nextLong();
		if (S1 < S2) {
			swap(S1, S2);
			swap(V1, V2);
		}
		long long lcm = LCM(S1, S2);
		long long greed = N / lcm;
		N = N % lcm;
		if (greed > 0) {
			N += lcm;
			greed--;
		}
		long long ret = 0;
		for (LL i = 0; i <= N / S1; ++i) {
			LL j = (N - i * S1) / S2;
			ret = max(ret, i * V1 + j * V2);
		}
		ret += greed * max((lcm / S1) * V1, (lcm / S2) * V2);
		printf("Case #%d: ", ++cases);
		outInteger(ret);
		printf("\n");
	}
	return 0;
}

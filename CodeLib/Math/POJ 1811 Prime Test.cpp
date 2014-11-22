/*
** POJ 1811 Prime Test
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int seed = 20;

inline void FixMod(Long& x, Long MOD) {
	while (x >= MOD) x -= MOD;
	while (x < 0) x += MOD;
}
Long Multiply(Long a, Long b, Long MOD) {
	a %= MOD, b %= MOD;
	Long ret = 0;
	while (b) {
		if (b & 1) {
			ret += a;
			FixMod(ret, MOD);
		}
		a <<= 1;
		FixMod(a, MOD);
		b >>= 1;
	}
	return ret;
}
Long QuickMod(Long x, Long n, Long MOD) {
	x %= MOD;
	if (n == 1) return x;
	Long ret = 1;
	while (n) {
		if (n & 1)
			ret = Multiply(ret, x, MOD);
		x = Multiply(x, x, MOD);
		n >>= 1;
	}
	return ret;
}
//以a为基, n - 1 = x*2^t
//a^(n-1) % n = 1 验证n是不是合数
bool Witness(Long a, Long n, Long x, Long t) {
	Long ret = QuickMod(a, x, n);
	Long last = ret;
	for (int i = 1; i <= t; ++i) {
		ret = Multiply(ret, ret, n);
		if (ret == 1 && last != 1 && last != n - 1)
			return true;
		last = ret;
	}
	if (ret != 1)
		return true;
	return false;
}
bool MillerRabin(Long n) {
	if (n == 2) return true;
	if (n < 2 || (n & 1) == 0) return false;
	Long x = n - 1, t = 0;
	while ((x & 1) == 0) {
		x >>= 1;
		++t;
	}
	for (int i = 0; i < seed; ++i) {
		Long a = rand() % (n - 1) + 1;
		if (Witness(a, n, x, t)) {
			return false;
		}
	}
	return true;
}

Long gcd(Long a, Long b) {
	if (a == 0) return 1;
	if (a < 0) return gcd(-a, b);
	return (b == 0) ? a : gcd(b, a % b);
}

Long PollardRho(Long x, Long c) {
	Long i = 1, k = 2;
	Long x0 = rand() % x, y = x0;
	while (true) {
		++i;
		x0 = (Multiply(x0, x0, x) + c) % x;
		Long g = gcd(y - x0, x);
		if (g != 1 && g != x) return g;
		if (y == x0) return x;
		if (i == k) {
			y = x0;
			k += k;
		}
	}
}

vector<Long> fact;

void FindFactor(Long n) {
	if (MillerRabin(n)) {
		fact.push_back(n);
		return;
	}
	Long p = n;
	while (p >= n) {
		p = PollardRho(p, rand() % (n - 1) + 1);
	}
	FindFactor(p);
	FindFactor(n / p);
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		Long n;
		scanf("%lld", &n);
		if (MillerRabin(n)) {
			printf("Prime\n");
			continue;
		}
		fact.clear();
		FindFactor(n);
		Long ret = 1LL << 60;
		for (vector<Long>::iterator it = fact.begin(); it != fact.end(); ++it) {
			ret = min(ret, *it);
		}
		printf("%lld\n", ret);
	}
	return 0;
}

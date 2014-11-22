/*
** POJ 3641 Pseudoprime numbers
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int MAXN = 1299709 + 10;

bool IsPrime(Long x) {
	if (x == 2) return true;
	if (x <= 1) return false;
	for (int i = 3; i * i <= x; ++i) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}
Long QucikPow(Long x, Long n, Long MOD) {
	Long ret = 1;
	while (n) {
		if (n & 1) ret = ret * x % MOD;
		x = x * x % MOD;
		n >>= 1;
	}
	return ret % MOD;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Long p, a;
	while (scanf("%lld%lld", &p, &a) != EOF && (p && a)) {
		if (IsPrime(p)) {
			puts("no");
			continue;
		}
		if (QucikPow(a, p, p) == a) {
			puts("yes");
		} else {
			puts("no");
		}
	}
	return 0;
}

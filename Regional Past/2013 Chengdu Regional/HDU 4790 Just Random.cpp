/*
** HDU 4790 Just Random
** Created by Rayn @@ 2014/10/27
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

Long p, m;

Long gcd(Long a, Long b) {
	return b == 0 ? a : gcd(b, a % b);
}
Long f(Long a, Long b) {
	if (a < 0 || b < 0) return 0;
	Long ma = a % p, mb = b % p;
	Long ret = (a / p) * (b / p) * p + (ma + 1) * (b / p) + (mb + 1) * (a / p);
	if (ma > m)  {
		ret += min(m + 1, mb + 1);
		Long tmp = (m - ma + p) % p;
		if (tmp <= mb) {
			ret += mb - tmp + 1;
		}
	} else {
		Long tmp = (m - ma + p) % p;
		if (tmp <= mb) {
			ret += min(m - tmp + 1, mb - tmp + 1);
		}
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		Long a, b, c, d;
		scanf("%I64d %I64d %I64d %I64d %I64d %I64d", &a, &b, &c, &d, &p, &m);
		Long tot = (b - a + 1) * (d - c + 1);
		Long ret = f(b, d) - f(a - 1, d) - f(b, c - 1) + f(a - 1, c - 1);
		Long g = gcd(tot, ret);
		printf("Case #%d: %I64d/%I64d\n", ++cases, ret / g, tot / g);
	}
	return 0;
}
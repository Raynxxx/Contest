/*
** CF 477A Dreamoon and Sums
** Created by Rayn @@ 2014/10/21
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
#include <functional>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MOD = 1000000007;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Long a, b;
	while (cin >> a >> b) {
		Long ret = 0;
		Long sumb = (b * (b - 1) / 2) % MOD;
		for (Long k = 1; k <= a; ++k) {
			Long x = (k * b + 1) % MOD;
			ret = (ret + x * sumb) % MOD;
		}
		cout << ret << endl;
	}
	return 0;
}

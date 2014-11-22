/*
** ZOJ 3745 Salary Increasing
** Created by Rayn @@ 2014/10/17
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
using namespace std;

typedef long long Long;
const int MAXN = 200050;

Long dp[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, q;
	while (scanf("%d%d", &n, &q) != EOF) {
		fill_n(dp, MAXN, 0);
		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			dp[x]++;
		}
		while (q--) {
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			for (int i = r; i >= l; --i) {
				dp[i + c] += dp[i];
				dp[i] = 0;
			}
		}
		Long ret = 0;
		for (int i = 0; i < MAXN; ++i) {
			ret += (Long)i * dp[i];
		}
		printf("%lld\n", ret);
	}
	return 0;
}

/*
** ZOJ 3416 Balanced Number
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

using namespace std;
typedef long long LL;
LL dp[20][2000];
int lim[20];

LL dfs(int pos, int mid, int lval, bool flag)
{
	if (pos == 0) return lval == 0;
	if (lval < 0) return 0;
	if (!flag && dp[pos][lval] != -1)
		return dp[pos][lval];
	LL sum = 0;
	int up = flag ? lim[pos] : 9;
	for (int i = 0; i <= up; ++i) {
		int next = lval + (pos - mid) * i;
		sum += dfs(pos - 1, mid, next, (flag && i == up));
	}
	if (!flag) dp[pos][lval] = sum;
	return sum;
}
LL Gao(LL x)
{
	int sz = 0;
	while (x) {
		lim[++sz] = x % 10;
		x /= 10;
	}
	LL ret = 0;
	for (int i = 1; i <= sz; i++) {
		memset(dp, -1, sizeof(dp));
		ret += dfs(sz, i, 0, true);
	}
	return ret - (sz - 1);
}

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		LL l, r;
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", Gao(r) - Gao(l - 1));
	}
	return 0;
}

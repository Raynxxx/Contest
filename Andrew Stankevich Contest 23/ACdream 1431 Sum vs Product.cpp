/*
** ACdream 1431 Sum vs Product
** Created by Rayn @@ 2014/10/31
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

int dp[512];

void dfs(Long mul, Long add, int cur, int last) {
	if (mul - add + cur > 500) return;
	if (cur >= 2) {
		dp[mul - add + cur]++;
	}
	for (int i = last; i <= 5000; ++i) {
		dfs(mul * i, add + i, cur + 1, i);
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	fill_n(dp, 512, 0);
	dfs(1, 0, 0, 2);
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%d\n", dp[n]);
	}
	return 0;
}

/*
** CF 464D World of Darkraft - 2
** Created by Rayn @@ 2014/10/13
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
const int MAXN = 100000 + 30;
const int LEVEL = 720;

double dp[2][LEVEL];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF) {
		memset(dp, 0, sizeof(dp));
		int cur = 0, pre = 1;
		for (int i = 1; i <= n; ++i) {
			swap(cur, pre);
			for (int j = 1; j <= 700; ++j) {
				dp[cur][j] = ((j * (dp[pre][j] + (j + 1) / 2.0) + dp[pre][j + 1] + j) / (j + 1) + dp[pre][j] * (k - 1)) / k;
			}
		}
		printf("%.10f\n", dp[cur][1] * k);
	}
	return 0;
}

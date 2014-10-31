/*
** ACdream 1429 Rectangular Polygon
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

const int MAXN = 105;
const int Balance = 20000;
const int MAXV = 40010;

int dp[MAXN][MAXV];
int pre[MAXN][MAXV];

void Gao(int n) {
	int lower = Balance - n * 200;
	int upper = Balance + n * 200;
	memset(pre, 0, sizeof(pre));
	memset(dp, -1, sizeof(dp));
	dp[0][Balance] = 0;
	for (int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		for (int j = lower; j <= upper; ++j) {
			if (dp[i][j] == -1) continue;
			if (dp[i + 1][j + x] < dp[i][j] + 1) {
				dp[i + 1][j + x] = dp[i][j] + 1;
				pre[i + 1][j + x] = j;
			}
			if (dp[i + 1][j - x] < dp[i][j] + 1) {
				dp[i + 1][j - x] = dp[i][j] + 1;
				pre[i + 1][j - x] = j;
			}
			if (dp[i + 1][j] < dp[i][j]) {
				dp[i + 1][j] = dp[i][j];
				pre[i + 1][j] = j;
			}
		}
	}
}
void GetPath(int n, int sz) {
	vector<int> top, bot;
	int st = Balance;
	for (int i = n; i >= 1; --i) {
		int path = pre[i][st];
		if (path > st) top.push_back(path - st);
		if (path < st) bot.push_back(st - path);
		st = path;
	}
	printf("%d\n", sz);
	int x = 0, y = 0;
	for (int i = 0; i < (int)bot.size(); ++i) {
		printf("%d %d\n", x, y);
		x += bot[i];
		printf("%d %d\n", x, y);
		++y;
	}
	for (int i = 0; i < (int)top.size(); ++i) {
		printf("%d %d\n", x, y);
		x -= top[i];
		printf("%d %d\n", x, y);
		++y;
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n;
	while (scanf("%d", &n) != EOF) {
		Gao(n);
		int sz = dp[n][Balance];
		if (sz == 0) {
			printf("%d\n", sz);
			continue;
		}
		GetPath(n, sz);
	}
	return 0;
}

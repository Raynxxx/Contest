/*
** ACdream 1421 TV Show
** Created by Rayn @@ 2014/10/28
*/
#include <map>
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
const int MAXN = 105;

int n;
double c;
double p[MAXN];

double dfs(int idx, double expect, bool buy) {
	if (idx >= n) return expect;
	double ret = max(expect, p[idx] * dfs(idx + 1, 2 * expect, buy));
	if (expect >= c && !buy) {
		expect -= c;
		ret = max(ret, dfs(idx + 1, p[idx] * 2 * expect + (1.0 - p[idx]) * expect, true));
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%lf", &n, &c) != EOF) {
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			p[i] = x / 100.0;
		}
		printf("%.8f\n", dfs(0, 100.0, false));
	}
	return 0;
}

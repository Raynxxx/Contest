/*
** CF 475C Kamal-ol-molk's Painting
** Created by Rayn @@ 2014/10/15
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
typedef long long LL;
const int MAXN = 1005;

int n, m;
char paint[MAXN][MAXN];
int sum[MAXN][MAXN];

int getSum(int x1, int y1, int x2, int y2) {
	return sum[x2 + 1][y2 + 1] - sum[x2 + 1][y1] - sum[x1][y2 + 1] + sum[x1][y1];
}
bool Check(int a, int b, int sx, int sy) {
	while (true) {
		if (sx + a > n || sy + b > m) {
			return false;
		}
		if (getSum(sx, sy, sx + a - 1, sy + b - 1) != a * b) {
			return false;
		}
		if ((sy + b == m || getSum(sx, sy + b, n - 1, m - 1) == 0) &&
			(sx + a == n || getSum(sx + a, sy, n - 1, m - 1) == 0)) {
			break;
		}
		if (sy + b < m && paint[sx][sy + b] == 'X') {
			if (sx + a < n && getSum(sx + a, sy, n - 1, sy) != 0) {
				return false;
			}
			++sy;
			continue;
		}
		if (sx + a < n && paint[sx + a][sy] == 'X') {
			if (sy + b < m && getSum(sx, sy + b, sx, m - 1) != 0) {
				return false;
			}
			++sx;
			continue;
		}
		return false;
	}
	return true;
}

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d", &n, &m) != EOF) {
		int sx = n, sy = m;
		for (int i = 0; i < n; ++i) {
			scanf("%s", paint[i]);
			for (int j = 0; j < m; ++j) {
				if (paint[i][j] == 'X') {
					sx = min(sx, i);
					sy = min(sy, j);
				}
			}
		}
		/*
		for (int i = 0; i < n; ++i) {
			printf("%s\n", paint[i]);
		}*/
		if (paint[sx][sy] != 'X') {
			puts("-1");
			continue;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + (paint[i][j] == 'X');
			}
		}
		int ans = MAXN * MAXN;
		for (int a = 1; a <= n; ++a) {
			for (int b = 1; b <= m; ++b) {
				if (a * b < ans) {
					if (Check(a, b, sx, sy)) {
						ans = a * b;
					}
				}
			}
		}
		if (ans > n * m) {
			ans = -1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

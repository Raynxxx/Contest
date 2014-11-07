/*
** CF 434B Nanami's Digital Board
** Created by Rayn @@ 2014/10/06
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 1005;

int n, m;
int pixel[MAXN][MAXN];
int toLeft[MAXN][MAXN], toRight[MAXN][MAXN];
int toTop[MAXN][MAXN], toBottom[MAXN][MAXN];
int length[MAXN];

void UpdateRow(int x) {
	for (int j = 1; j <= m; ++j) {
		if (pixel[x][j]) {
			toLeft[x][j] = toLeft[x][j - 1] + 1;
		} else {
			toLeft[x][j] = 0;
		}
	}
	for (int j = m; j >= 1; --j) {
		if (pixel[x][j]) {
			toRight[x][j] = toRight[x][j + 1] + 1;
		} else {
			toRight[x][j] = 0;
		}
	}
}
void UpdateCol(int y) {
	for (int i = 1; i <= n; ++i) {
		if (pixel[i][y]) {
			toTop[i][y] = toTop[i - 1][y] + 1;
		} else {
			toTop[i][y] = 0;
		}
	}
	for (int i = n; i >= 1; --i) {
		if (pixel[i][y]) {
			toBottom[i][y] = toBottom[i + 1][y] + 1;
		}
		else {
			toBottom[i][y] = 0;
		}
	}
}
int nextGao(int mid, int height, int range) {
	int left = mid, right = mid;
	int ret = 0;
	for (int h = height; h >= 1; --h) {
		while (left >= 1 && length[left] >= h) {
			left--;
		}
		while (right <= range && length[right] >= h) {
			right++;
		}
		ret = max(ret, h * (right - left - 1));
	}
	return ret;
}
int Gao(int x, int y) {
	int ret = 0;
	for (int j = 1; j <= m; ++j) {
		length[j] = toTop[x][j];
	}
	ret = max(ret, nextGao(y, length[y], m));
	for (int j = 1; j <= m; ++j) {
		length[j] = toBottom[x][j];
	}
	ret = max(ret, nextGao(y, length[y], m));
	for (int i = 1; i <= n; ++i) {
		length[i] = toLeft[i][y];
	}
	ret = max(ret, nextGao(x, length[x], n));
	for (int i = 1; i <= n; ++i) {
		length[i] = toRight[i][y];
	}
	ret = max(ret, nextGao(x, length[x], n));
	return ret;
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int q;
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &pixel[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			UpdateRow(i);
		}
		for (int j = 1; j <= m; ++j) {
			UpdateCol(j);
		}
		while (q--) {
			int op, x, y;
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				pixel[x][y] ^= 1;
				UpdateRow(x);
				UpdateCol(y);
			} else {
				printf("%d\n", Gao(x, y));
			}
		}
	}
	return 0;
}

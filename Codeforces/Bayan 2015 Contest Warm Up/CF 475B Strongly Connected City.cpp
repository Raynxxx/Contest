/*
** CF 475B Strongly Connected City
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

const int MAXN = 25;

int n, m, dep;
char hor[MAXN], ver[MAXN];
bool vis[MAXN][MAXN];

void Init() {
	dep = 0;
	memset(vis, false, sizeof(vis));
}
bool OutRange(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= m)
		return true;
	return false;
}
void Find(int x, int y) {
	if (OutRange(x, y) || vis[x][y])
		return;
	vis[x][y] = true;
	dep++;
	if (hor[x] == '>') {
		Find(x, y + 1);
	} else {
		Find(x, y - 1);
	}
	if (ver[y] == 'v') {
		Find(x + 1, y);
	} else {
		Find(x - 1, y);
	}
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d", &n, &m) != EOF) {
		scanf("%s%s", hor, ver);
		bool ok = true;
		for (int i = 0; i < n && ok; ++i) {
			for (int j = 0; j < m && ok; ++j) {
				Init();
				Find(i, j);
				if (dep != n * m) {
					ok = false;
					break;
				}
			}
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}

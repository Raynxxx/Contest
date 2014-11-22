/*
** LA 6663 Count the Regions
** Created by Rayn @@ 2014/10/15
*/
//#pragma comment(linker, "/STACK:102400000,102400000")
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
typedef vector<int>::iterator Iter;
const int MAXN = 256;
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };

int n;
int l[MAXN], r[MAXN];
int t[MAXN], b[MAXN];
bool maze[MAXN][MAXN];
vector<int> setx, sety;
map<int, int> mx, my;

void Init() {
	setx.clear(), sety.clear();
	mx.clear(), my.clear();
	memset(maze, false, sizeof(maze));
}
void MakeHash() {
	sort(setx.begin(), setx.end());
	sort(sety.begin(), sety.end());
	setx.erase(unique(setx.begin(), setx.end()), setx.end());
	sety.erase(unique(sety.begin(), sety.end()), sety.end());
	int sx = 1;
	for (Iter it = setx.begin(); it != setx.end(); ++it) {
		mx[*it] = sx;
		sx += 2;
	}
	int sy = 1;
	for (Iter it = sety.begin(); it != sety.end(); ++it) {
		my[*it] = sy;
		sy += 2;
	}
	for (int i = 0; i < n; ++i) {
		l[i] = mx[l[i]], r[i] = mx[r[i]];
		b[i] = my[b[i]], t[i] = my[t[i]];
	}
	for (int i = 0; i < n; ++i) {
		for (int x = l[i]; x <= r[i]; ++x) {
			maze[x][b[i]] = true;
			maze[x][t[i]] = true;
		}
		for (int y = b[i]; y <= t[i]; ++y) {
			maze[l[i]][y] = true;
			maze[r[i]][y] = true;
		}
	}
}
bool OutRange(int x, int y) {
	if (x < 0 || y < 0 || x >= 210 || y >= 210)
		return true;
	return false;
}
void dfs(int x, int y) {
	maze[x][y] = true;
	for (int i = 0; i < 4; ++i) {
		int px = x + dx[i];
		int py = y + dy[i];
		if (!OutRange(px, py) && !maze[px][py]) {
			dfs(px, py);
		}
	}
}
int Gao() {
	int color = 0;
	for (int i = 0; i < 210; ++i) {
		for (int j = 0; j < 210; ++j) {
			if (!maze[i][j]) {
				color++;
				dfs(i, j);
			}
		}
	}
	return color;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d", &n) != EOF && n) {
		Init();
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &l[i], &t[i], &r[i], &b[i]);
			setx.push_back(l[i]);
			setx.push_back(r[i]);
			sety.push_back(t[i]);
			sety.push_back(b[i]);
		}
		MakeHash();
		printf("%d\n", Gao());
	}
	return 0;
}

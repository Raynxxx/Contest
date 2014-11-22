/*
** ZOJ 3420 Double Maze
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

const char dir[] = { 'D', 'L', 'R', 'U' };
const int move[][2] = { { 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 } };

struct State {
	int x1, y1, x2, y2;
	State() {}
	State(int x1, int y1, int x2, int y2) :
		x1(x1), y1(y1), x2(x2), y2(y2) {}
	bool operator == (const State& rhs) const {
		return (x1 == rhs.x1 && y1 == rhs.y1)
			&& (x2 == rhs.x2 && y2 == rhs.y2);
	}
};

int maze[25][10][10];
int g1[10][10], g2[10][10];
bool vis[10][10][10][10];
char path[10][10][10][10];
State pre[10][10][10][10];
State win;
int sx1, sy1, ex1, ey1;
int sx2, sy2, ex2, ey2;

bool outRange(int x, int y) {
	if (x < 0 || y < 0 || x >= 6 || y >= 6)
		return true;
	return false;
}
bool Safe(int x1, int y1, int x2, int y2) {
	if (!(g1[x1][y1] & (1 << 4)) || !(g2[x2][y2] & (1 << 4)))
		return false;
	return true;
}
bool bfs() {
	win = State(ex1, ey1, ex2, ey2);
	memset(vis, false, sizeof(vis));
	queue<State> que;
	que.push(State(sx1, sy1, sx2, sy2));
	vis[sx1][sy1][sx2][sy2] = true;
	path[sx1][sy1][sx2][sy2] = '0';
	while (!que.empty()) {
		State cur = que.front();
		que.pop();
		int x1 = cur.x1, y1 = cur.y1;
		int x2 = cur.x2, y2 = cur.y2;
		if (cur == win) {
			return true;
		}
		for (int i = 0; i < 4; ++i) {
			int px1 = x1, py1 = y1;
			int px2 = x2, py2 = y2;
			if (i == 0) {
				if (!(g1[x1][y1] & (1 << 1)))
					px1++;
				if (!(g2[x2][y2] & (1 << 1)))
					px2++;
			} else if (i == 1) {
				if (!(g1[x1][y1] & 1))
					py1--;
				if (!(g2[x2][y2] & 1))
					py2--;
			} else if (i == 2) {
				if (!(g1[x1][y1] & (1 << 2)))
					py1++;
				if (!(g2[x2][y2] & (1 << 2)))
					py2++;
			} else if (i == 3) {
				if (!(g1[x1][y1] & (1 << 3)))
					px1--;
				if (!(g2[x2][y2] & (1 << 3)))
					px2--;
			}
			if (outRange(px1, py1) || outRange(px2, py2))
				continue;
			if (!Safe(px1, py1, px2, py2))
				continue;
			if (!vis[px1][py1][px2][py2]) {
				vis[px1][py1][px2][py2] = true;
				path[px1][py1][px2][py2] = dir[i];
				pre[px1][py1][px2][py2] = cur;
				que.push(State(px1, py1, px2, py2));
			}
		}
	}
	return false;
}
void PrintPath(State st) {
	if (path[st.x1][st.y1][st.x2][st.y2] != '0') {
		PrintPath(pre[st.x1][st.y1][st.x2][st.y2]);
		putchar(path[st.x1][st.y1][st.x2][st.y2]);
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	for (int k = 0; k < T; ++k) {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				scanf("%d", &maze[k][i][j]);
			}
		}
	}
	for (int k = 1; k < T; ++k) {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				g1[i][j] = maze[k - 1][i][j];
				g2[i][j] = maze[k][i][j];
				if (g1[i][j] & (1 << 5)) {
					sx1 = i, sy1 = j;
				}
				if (g1[i][j] & (1 << 6)) {
					ex1 = i, ey1 = j;
				}
				if (g2[i][j] & (1 << 5)) {
					sx2 = i, sy2 = j;
				}
				if (g2[i][j] & (1 << 6)) {
					ex2 = i, ey2 = j;
				}
			}
		}
		if (!bfs())  {
			printf("-1\n");
		} else {
			PrintPath(win);
			putchar('\n');
		}
	}
	return 0;
}

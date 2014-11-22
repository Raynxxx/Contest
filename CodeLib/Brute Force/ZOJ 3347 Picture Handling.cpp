/*
** ZOJ 3347 Picture Handling
** Created by Rayn @@ 2014/10/18
*/
#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace FastIO {
	/* Input >> int & long long */
	template <typename T>
	inline void readInteger(T& ret) {
		char ch = getchar();
		bool flag = false;
		while ((ch < '0' || ch > '9') && ch != '-') {
			ch = getchar();
		}
		if (ch == '-') {
			flag = true;
			ch = getchar();
		}
		ret = 0;
		while (ch >= '0' && ch <= '9') {
			ret = ret * 10 + (ch - '0');
			ch = getchar();
		}
		if (flag) ret = -ret;
	}
	inline int nextInt() {
		int x;
		readInteger(x);
		return x;
	}
	inline long long nextLong() {
		long long x;
		readInteger(x);
		return x;
	}

	/* Output << int & long long */
	template <typename T>
	inline void outInteger(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x >= 10) {
			outInteger(x / 10);
		}
		putchar(x % 10 + '0');
	}
	inline void newline() {
		putchar('\n');
	}
};

using namespace std;
using namespace FastIO;
const int MAXN = 300;
const int MAXM = 100010;

struct QueryNode {
	int x1, y1, x2, y2;
	int op;
	inline void read() {
		x1 = nextInt();
		y1 = nextInt();
		x2 = nextInt();
		y2 = nextInt();
		op = nextInt();
	}
	inline bool InRange(int x, int y) {
		return x1 <= x && x <= x2 && y1 <= y && y <= y2;
	}
};

int picture[MAXN][MAXN];
QueryNode cmd[MAXM];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int W, H;
	while (scanf("%d%d", &W, &H) != EOF) {
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				picture[i][j] = nextInt();
			}
		}
		int M = nextInt();
		for (int i = 0; i < M; ++i) {
			cmd[i].read();
		}
		int x = nextInt();
		int y = nextInt();
		int change = 1, add = 0;
		for (int i = M - 1; i >= 0; --i) {
			if (cmd[i].InRange(x, y)) {
				if (cmd[i].op == 1) {
					change = -change;
					add = -add;
				} else if(cmd[i].op == 2) {
					++add;
				} else if (cmd[i].op == 3) {
					--add;
				} else if (cmd[i].op == 4) {
					x = cmd[i].x1 + cmd[i].x2 - x;
				} else {
					y = cmd[i].y1 + cmd[i].y2 - y;
				}
			}
		}
		int ret = (picture[y][x] + add) * change;
		outInteger(ret);
		newline();
	}
	return 0;
}

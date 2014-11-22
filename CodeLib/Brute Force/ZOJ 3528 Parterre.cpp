/*
** ZOJ 3528 Parterre
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAXN = 512;

int maze[MAXN][MAXN];
int cnt[MAXN/2];


int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m, q;
	while (scanf("%d%d", &n, &m) != EOF) {
		int line = (int)ceil(min(n, m) / 2.0);
		for (int i = 1; i <= line; ++i) {
			int type;
			scanf("%d", &type);
			for (int j = i; j <= (n - i + 1); ++j) {
				maze[j][i] = type;
				maze[j][m - i + 1] = type;
			}
			for (int j = i; j <= (m - i + 1); ++j) {
				maze[i][j] = type;
				maze[n - i + 1][j] = type;
			}
		}
		scanf("%d", &q);
		while (q--) {
			int top, left, bot, right;
			scanf("%d%d%d%d", &top, &left, &bot, &right);
			top++, left++, bot++, right++;
			memset(cnt, 0, sizeof(cnt));
			int max_id = 0;
			for (int i = top; i <= bot; ++i) {
				for (int j = left; j <= right; ++j) {
					cnt[maze[i][j]]++;
					max_id = max(max_id, maze[i][j]);
				}
			}
			int TOTAL = 0, INDEX = 0, COUNT = 0;
			for (int i = 1; i <= max_id; ++i) {
				if (cnt[i]) {
					TOTAL++;
					if (cnt[i] > COUNT) {
						COUNT = cnt[i];
						INDEX = i;
					}
				}
			}
			printf("%d %d %d\n", TOTAL, INDEX, COUNT);
		}
	}
	return 0;
}

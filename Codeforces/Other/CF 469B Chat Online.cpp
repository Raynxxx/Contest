/*
** CF 469B Chat Online
** Created by Rayn @@ 2014/10/08
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
const int MAXN = 64;

struct TimeTable {
	int l, r;
	TimeTable() {}
	TimeTable(int l, int r) : l(l), r(r) {}
};

TimeTable LittleX[MAXN];
TimeTable LittleZ[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int p, q, l, r;
	while (scanf("%d%d%d%d", &p, &q, &l, &r) != EOF) {
		for (int i = 1; i <= p; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			LittleZ[i] = TimeTable(a, b);
		}
		for (int i = 1; i <= q; ++i) {
			int c, d;
			scanf("%d%d", &c, &d);
			LittleX[i] = TimeTable(c, d);
		}
		int ret = 0;
		for (int t = l; t <= r; ++t) {
			bool happy = false;
			for (int i = 1; i <= p && !happy; ++i) {
				for (int j = 1; j <= q && !happy; ++j) {
					if (LittleZ[i].r >= LittleX[j].l + t && LittleZ[i].l <= LittleX[j].r + t) {
						happy = true;
					}
				}
			}
			if (happy) {
				ret++;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

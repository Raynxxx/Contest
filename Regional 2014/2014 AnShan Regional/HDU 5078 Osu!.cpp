/*
** HDU 5078 Osu!
** Created by Rayn @@ 2014/10/30
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
const int MAXN = 1010;

struct Point {
	double x, y, t;
	void read() {
		scanf("%lf%lf%lf", &t, &x, &y);
	}
};

Point pt[MAXN];

double f(Point& a, Point& b) {
	return hypot(a.x - b.x, a.y - b.y) / (b.t - a.t);
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			pt[i].read();
		}
		double ret = -1;
		for (int i = 0; i < n; ++i) {
			ret = max(ret, f(pt[i], pt[i + 1]));
		}
		printf("%.10f\n", ret);
	}
	return 0;
}

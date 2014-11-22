/*
** ZOJ 3743 The Lambs
** Created by Rayn @@ 2014/10/17
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

typedef long long Long;
const int MAXN = 105;
const int MAXM = 1005;
const double INF = 1e20;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}

	void read() {
		scanf("%d%d", &x, &y);
	}
	Point operator - (const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};

inline double sqr(double x) {
	return x * x;
}
inline int Cross(const Point& A, const Point& B) {
	return A.x * B.y - A.y * B.x;
}
inline double Dist(const Point& A, const Point& B) {
	return sqrt(sqr((double)A.x - B.x) + sqr((double)A.y - B.y));
}

int n, m;
Point stake[MAXN];
Point lamb[MAXM];
double dis[MAXN][MAXN];

double Floyd() {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	double circle = INF;
	for (int i = 1; i <= n; ++i) {
		circle = min(circle, dis[i][i]);
	}
	return circle;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			stake[i].read();
		}
		for (int i = 1; i <= m; ++i) {
			lamb[i].read();
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				bool flag = true;
				for (int k = 1; k <= m; ++k) {
					if (Cross(stake[j] - stake[i], lamb[k] - stake[i]) <= 0) {
						flag = false;
						break;
					}
				}
				if (flag == true) {
					dis[i][j] = Dist(stake[i], stake[j]);
				} else {
					dis[i][j] = INF;
				}
			}
		}
		printf("%.10f\n", Floyd());
	}
	return 0;
}

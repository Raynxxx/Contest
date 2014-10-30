/*
** ACdream 1414 Geometry Problem
** Created by Rayn @@ 2014/10/28
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
typedef long long Long;
const double EPS = 1e-3;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	bool isZero() {
		return x == 0 && y == 0;
	}
	Point operator + (const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator / (const double& p) const {
		return Point(x / p, y / p);
	}
};

int dcmp(double x) {
	if (fabs(x) < EPS)
		return 0;
	return (x < 0) ? -1 : 1;
}
inline double sqr(double x) {
	return x * x;
}
double Dist(const Point& a, const Point& b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Point st1, ed1, st2, ed2;
	double d[5];
	while (scanf("%lf%lf%lf%lf", &st1.x, &st1.y, &ed1.x, &ed1.y) != EOF) {
		scanf("%lf%lf%lf%lf", &st2.x, &st2.y, &ed2.x, &ed2.y);
		if (st1.isZero() && ed1.isZero() && st2.isZero() && ed2.isZero()) {
			break;
		}
		d[1] = Dist(st1, st2);
		d[2] = Dist(st1, ed2);
		d[3] = Dist(ed1, st2);
		d[4] = Dist(ed1, ed2);
		double D = min(min(d[1], d[2]), min(d[3], d[4]));
		Point circle;
		if (dcmp(D - d[1]) == 0) {
			circle = (st1 + st2) / 2.0;
		} else if (dcmp(D - d[2]) == 0) {
			circle = (st1 + ed2) / 2.0;
		} else if (dcmp(D - d[3]) == 0) {
			circle = (ed1 + st2) / 2.0;
		} else if (dcmp(D - d[4]) == 0) {
			circle = (ed1 + ed2) / 2.0;
		}
		double r = D / 2.0 + EPS;
		printf("%f %f %f\n", circle.x, circle.y, r);
	}
	return 0;
}

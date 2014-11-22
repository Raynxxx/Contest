/*
** ZOJ 3421 Error Curves
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
const int MAXN = 10000 + 10;
const double EPS = 1e-10;
const double INF = 1e24;

int n;
double a[MAXN];
double b[MAXN];
double c[MAXN];

double F(double x) {
	double maxs = -INF;
	for (int i = 1; i <= n; ++i) {
		double s = a[i] * x * x + b[i] * x + c[i];
		maxs = max(maxs, s);
	}
	return maxs;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lf%lf%lf", &a[i], &b[i], &c[i]);
		}
		double L = 0, R = 1000;
		while (L + EPS < R) {
			double mid1 = L + (R - L) / 3.0;
			double mid2 = R - (R - L) / 3.0;
			if (F(mid1) < F(mid2)) {
				R = mid2;
			} else {
				L = mid1;
			}
		}
		printf("%.4f\n", F(L));
	}
	return 0;
}

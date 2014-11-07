/*
** CF 475D CGCDSSQ
** Created by Rayn @@ 2014/10/16
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
const int MAXN = 100005;

int a[MAXN];
pair<int, long long> divisor[MAXN];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}
void Gao(int n, map<int, long long>& res) {
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < top; ++j) {
			divisor[j].first = gcd(divisor[j].first, a[i]);
		}
		divisor[top++] = make_pair(a[i], 1);
		int pt = 1;
		for (int j = 1; j < top; ++j) {
			if (divisor[pt - 1].first == divisor[j].first) {
				divisor[pt - 1].second += divisor[j].second;
			} else {
				divisor[pt++] = divisor[j];
			}
		}
		top = pt;
		for (int j = 0; j < top; ++j) {
			res[divisor[j].first] += divisor[j].second;
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, q, x;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		map<int, long long> res;
		Gao(n, res);
		scanf("%d", &q);
		while (q--) {
			scanf("%d", &x);
			printf("%I64d\n", res[x]);
		}
	}
	return 0;
}

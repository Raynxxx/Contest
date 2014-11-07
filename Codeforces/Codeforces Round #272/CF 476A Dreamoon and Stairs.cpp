/*
** CF 476A Dreamoon and Stairs
** Created by Rayn @@ 2014/10/21
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
#include <functional>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 10010;

int main() {
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		int ret = -1;
		for (int i = (n + 1) / 2; i <= n; ++i) {
			if (i % m == 0) {
				ret = i;
				break;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

/*
** CF 477B Dreamoon and Sets
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

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF) {
		printf("%d\n", (n * 6 - 1) * k);
		int a = 1;
		for (int i = 1; i <= n; ++i) {
			printf("%d %d %d %d\n", a * k, (a + 1) * k, (a + 2) * k, (a + 4) * k);
			a += 6;
		}
	}
	return 0;
}

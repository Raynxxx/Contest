/*
** ACdream 1417 Numbers
** Created by Rayn @@ 2014/10/30
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

Long QuickPow(Long x, int n) {
	Long ret = 1;
	while (n) {
		if (n & 1) ret = ret * x;
		x = x * x;
		n >>= 1;
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Long n, k;
	char ret[25], tmp[25];
	while (scanf("%lld%lld", &n, &k) != EOF && (n || k)) {
		sprintf(ret, "%lld", k);
		int low = strlen(ret);
		for (int i = low; i <= 18; ++i) {
			Long cur = QuickPow(10, i);
			if (cur > n) break;
			if (cur % k == 0) {
				sprintf(tmp, "%lld", cur);
				if (strcmp(tmp, ret) < 0) {
					strcpy(ret, tmp);
				}
			}
			Long next = cur / k * k + k;
			if (next > n) continue;
			if (next % k == 0) {
				sprintf(tmp, "%lld", next);
				if (strcmp(tmp, ret) < 0) {
					strcpy(ret, tmp);
				}
			}
		}
		printf("%s\n", ret);
	}
	return 0;
}

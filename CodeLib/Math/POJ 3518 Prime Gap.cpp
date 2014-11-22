/*
** POJ 3518 Prime Gap
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int MAXN = 1299709 + 10;

bool flag[MAXN];
int prime[MAXN];

int GetPrime() {
	memset(flag, true, sizeof(flag));
	flag[0] = flag[1] = false;
	int sz = 0;
	for (int i = 2; i < MAXN; ++i) {
		if (flag[i]) {
			prime[sz++] = i;
			for (int j = i * 2; j < MAXN; j += i) {
				flag[j] = false;
			}
		}
	}
	return sz;
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int pcnt = GetPrime();
	int n;
	while (scanf("%d", &n) != EOF && n) {
		if (flag[n]) {
			printf("0\n");
			continue;
		}
		int upper = upper_bound(prime, prime + pcnt, n) - prime;
		int lower = upper - 1;
		printf("%d\n", prime[upper] - prime[lower]);
	}
	return 0;
}

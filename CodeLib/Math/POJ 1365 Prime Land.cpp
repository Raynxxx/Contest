/*
** POJ 1365 Prime Land
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
typedef pair<int, int> PII;
const int MAXN = 35000;

bool flag[MAXN];
int prime[MAXN];
PII ret[MAXN];

int GetPrime() {
	memset(flag, true, sizeof(flag));
	int sz = 0;
	flag[0] = flag[1] = false;
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
int QuickPow(int x, int n) {
	int ret = 1;
	while (n) {
		if (n & 1) ret = ret * x;
		x = x * x;
		n >>= 1;
	}
	return ret;
}
void Solve(int pcnt, int num) {
	bool first = true;
	int top = 0;
	for (int i = 0; i < pcnt && prime[i] <= num; ++i) {
		if (num % prime[i] == 0) {
			int p = prime[i], e = 0;
			while (num % p == 0) {
				e++;
				num /= p;
			}
			ret[top++] = make_pair(p, e);
		}
	}
	for (int i = top - 1; i >= 0; --i) {
		printf("%d %d%c", ret[i].first, ret[i].second, (i == 0) ? '\n' : ' ');
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int pcnt = GetPrime();
	while (true) {
		int sum = 1;
		while (true) {
			int p, e;
			scanf("%d", &p);
			if (p == 0) return 0;
			scanf("%d", &e);
			sum = sum * QuickPow(p, e);
			if (getchar() == '\n') {
				break;
			}
		}
		Solve(pcnt, sum - 1);
	}
	return 0;
}

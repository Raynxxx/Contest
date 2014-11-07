/*
** HDU 5072 Coprime
** Created by Rayn @@ 2014/10/30
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
const int MAXN = 100010;

int number[MAXN];
int multi[MAXN];

void FindFactor(int p, vector<int>& fact) {
	int limit = (int) sqrt(p);
	for (int i = 2; i <= limit && p > 1; ++i) {
		if (p % i == 0) {
			fact.push_back(i);
			while (p % i == 0) {
				p /= i;
			}
		}
	}
	if (p > 1) fact.push_back(p);
}
Long Gao(int n, vector<int>& fact) {
	int sz = fact.size();
	int ret = 0;
	for (int i = 1; i < (1 << sz); ++i) {
		int flag = 0, tmp = 1;
		for (int j = 0; j < sz; ++j) {
			if ((i >> j) & 1) {
				flag++;
				tmp *= fact[j];
			}
		}
		if (flag & 1) ret += multi[tmp];
		else ret -= multi[tmp];
	}
	return (Long)max(0, ret - 1) * (n - ret);
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
		fill_n(number, MAXN, 0);
		fill_n(multi, MAXN, 0);
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			number[x]++;
		}
		for (int i = 1; i < MAXN; ++i) {
			for (int j = i; j < MAXN; j += i) {
				multi[i] += number[j];
			}
		}
		Long sub = 0;
		for (int i = 1; i < MAXN; ++i) {
			if (number[i] > 0) {
				vector<int> fact;
				FindFactor(i, fact);
				if (fact.empty()) continue;
				sub += Gao(n, fact);
			}
		}
		Long ret = (Long)n * (n - 1) * (n - 2) / 6 - sub / 2;
		printf("%I64d\n", ret);
	}
 	return 0;
}

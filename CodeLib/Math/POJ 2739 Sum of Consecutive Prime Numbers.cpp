/*
** POJ 2739 Sum of Consecutive Prime Numbers
** Created by Rayn @@ 2014/10/30
*/
#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
const int MAXP = 10010;
bool is_prime[MAXP];
int pcnt, prime[MAXP];

void prime_table() {
	fill_n(is_prime, MAXP, true);
	is_prime[0] = is_prime[1] = false;
	pcnt = 0;
	for (int i = 2; i < MAXP; ++i) {
		if (is_prime[i]) {
			prime[pcnt++] = i;
			for (int j = i * 2; j < MAXP; j += i) {
				is_prime[j] = false;
			}
		}
	}
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	prime_table();
	int n;
	while (scanf("%d", &n) != EOF && n) {
		int ret = 0;
		for (int i = 0; prime[i] <= n; ++i) {
			int sum = 0;
			for (int j = i; sum <= n; ++j) {
				sum += prime[j];
				if (sum == n) {
					ret++;
					break;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

/*
** ZOJ 3520 Hello, Gensokyo
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN = 100010;

LL dp[MAXN];

void Init() {
	dp[1] = 0;
	dp[2] = 1;
	dp[3] = 2;
	for (int i = 4; i < MAXN; ++i) {
		dp[i] = dp[i - 1] + (LL)i / 2;
	}
}
int main() {
	Init();
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%lld\n", dp[n]);
	}
}

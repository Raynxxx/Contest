/*
** HDU 4472 Count
** Created by Rayn @@ 2014/10/03
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MOD = (int)1e9 + 7;

int dp[MAXN];

void Gao() {
    dp[1] = dp[2] = 1;
    for(int i = 3; i < MAXN; ++i) {
        for(int j = 1; j < i; ++j) {
            if((i-1) % j == 0) {
                dp[i] += dp[(i-1)/j];
                dp[i] %= MOD;
            }
        }
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Gao();
    int n, cases = 0;
    while(scanf("%d", &n) != EOF) {
        printf("Case %d: %d\n", ++cases, dp[n]);
    }
    return 0;
}

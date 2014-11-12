/*
** CF 479E Riding in a Lift
** Created by Rayn @@ 2014/11/12
*/
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

const int MAXN = 5010;
const int MOD = 1000000007;

int dp[MAXN][MAXN];

void Add(int idx, int l, int r, int d) {
    dp[idx][l] = (dp[idx][l] + d) % MOD;
    dp[idx][r] = (dp[idx][r] - d + MOD) % MOD;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N, A, B, K;
    while (scanf("%d%d%d%d", &N, &A, &B, &K) != EOF) {
        memset(dp, 0, sizeof(dp));
        dp[0][A] = 1;
        for (int i = 0; i < K; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (j == B) continue;
                int range = abs(j - B) - 1;
                Add(i + 1, max(j - range, 1), j, dp[i][j]);
                Add(i + 1, j + 1, min(j + range, N) + 1, dp[i][j]);
            }
            for (int j = 1; j <= N; ++j) {
                dp[i + 1][j] = (dp[i + 1][j] + dp[i + 1][j - 1]) % MOD;
            }
        }
        int ret = 0;
        for (int i = 1; i <= N; ++i) {
            ret = (ret + dp[K][i]) % MOD;
        }
        printf("%d\n", ret);
    }
    return 0;
}

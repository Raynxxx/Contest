/*
** HDU 4049 Tourism Planning
** Created by Rayn @@ 2014/11/04
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 15;
const int ALL = 1 << 11;
const int INF = 0x3F3F3F3F;

int cost[MAXN];
int love[MAXN][MAXN];
int bonus[MAXN][MAXN];
int next_state[ALL][ALL], cnt[ALL];
int dp[MAXN][ALL], sum[MAXN][ALL];

inline void Init() {
    fill_n(cnt, ALL, 0);
    for (int i = 0; i < (1 << 10); ++i) {
        for (int j = 0; j < (1 << 10); ++j) {
            if ((i & j) == j) {
                next_state[i][cnt[i]++] = j;
            }
        }
    }
}
inline void gmax(int& a, int b) {
    if (b > a) a = b;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF && (n || m)) {
        for (int i = 0; i < m; ++i) {
            scanf("%d", &cost[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &love[i][j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &bonus[i][j]);
            }
        }
        memset(dp, -INF, sizeof(dp));
        memset(sum, 0, sizeof(sum));
        for (int p = 0; p < m; ++p) {
            for (int s = 0; s < (1 << n); ++s) {
                for (int i = 0; i < n; ++i) {
                    if ((s & (1 << i)) == 0) continue;
                    sum[p][s] += love[i][p] - cost[p];
                    for (int j = i - 1; j >= 0; --j) {
                        if (s & (1 << j)) {
                            sum[p][s] += bonus[i][j];
                        }
                    }
                }
            }
        }
        for (int s = 0; s < (1 << n); ++s) {
            dp[0][s] = max(dp[0][s], sum[0][s]);
        }
        for (int p = 1; p < m; ++p) {
            for (int s = 0; s < (1 << n); ++s) {
                for (int i = 0; i < cnt[s]; ++i) {
                    gmax(dp[p][next_state[s][i]], dp[p - 1][s] + sum[p][next_state[s][i]]);
                }
            }
        }
        int ret = -INF;
        for (int s = 0; s < (1 << n); ++s) {
            if (dp[m - 1][s] > ret) {
                ret = dp[m - 1][s];
            }
        }
        if (ret > 0) {
            printf("%d\n", ret);
        } else {
            printf("STAY HOME\n");
        }
    }
    return 0;
}

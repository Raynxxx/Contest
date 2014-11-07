/*
** HDU 5092 Seam Carving
** Created by Rayn @@ 2014/11/02
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long Long;
const int MAXN = 105;
const int INF = 0x3F3F3F3F;
const int dy[] = { 1, 0, -1 };

int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];
int pre[MAXN][MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while (T--) {
        int m, n;
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &matrix[i][j]);
            }
        }
        memset(dp, INF, sizeof(dp));
        memset(pre, -1, sizeof(pre));
        fill_n(dp[0], n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int py = j + dy[k];
                    if (py >= 1 && py <= n && dp[i][j] > dp[i - 1][py] + matrix[i][j]) {
                        dp[i][j] = dp[i - 1][py] + matrix[i][j];
                        pre[i][j] = k;
                    }
                }
            }
        }
        int minv = INF, y = -1;
        for (int i = 1; i <= n; ++i) {
            if (dp[m][i] <= minv) {
                minv = dp[m][i];
                y = i;
            }
        }
        vector<int> seam;
        int x = m;
        while (pre[x][y] != -1) {
            seam.push_back(y);
            y = y + dy[pre[x][y]];
            --x;
        }
        printf("Case %d\n", ++cases);
        int sz = seam.size();
        for (int i = sz - 1; i >= 0; --i) {
            printf("%d%c", seam[i], (i == 0) ? '\n' : ' ');
        }
    }
    return 0;
}

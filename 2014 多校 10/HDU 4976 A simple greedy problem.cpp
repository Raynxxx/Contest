/*
** HDU 4976 A simple greedy problem
** Created by Rayn @@ 2014/08/29
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int MAXN = 1001;

int creep[MAXN];
int cost[MAXN];
int dp[MAXN][MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;

    scanf("%d", &T);
    while (T--)
    {
        int N, maxv = 0;
        scanf("%d", &N);
        for(int i = 0; i < N; ++i) {
            scanf("%d", &creep[i]);
            if(creep[i] > maxv) maxv = creep[i];
        }
        sort(creep, creep + N);
        memset(cost, 0, sizeof(cost));
        for(int i = 0; i < N; ++i) {
            int times = 1;
            while(cost[creep[i]] && creep[i] > 0) {
                creep[i]--;
                times++;
            }
            if(creep[i] > 0) {
                cost[creep[i]] = times;
            }
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 0;
        for(int i = 1; i <= maxv; ++i) {
            for(int j = 0; j <= i; ++j) {
                if(j >= 1) {
                    dp[i][j] = dp[i-1][j-1];
                }
                if(cost[i] && j + cost[i] <= i) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1+cost[i]] + 1);
                }
            }
        }
        int res = 0;
        for(int j = 0; j <= maxv; ++j) {
            res = max(res, dp[maxv][j]);
        }
        printf("Case #%d: %d\n", ++cases, res);
    }
    return 0;
}

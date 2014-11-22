/*
** ZOJ 3463 Piano
** Created by Rayn @@ 2014/08/11
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const int maxm = 52;
const int INF = 0x3F3F3F3F;

int dp[2][maxm][maxm];
int msqrt[100];

void Init()
{
    for(int i = 0; i < 100; ++i)
    {
        msqrt[i] = (int)floor(sqrt(i));
    }
}

int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();

    int n, l, r, pos;
    while(scanf("%d%d%d", &l, &r, &n) != EOF)
    {
        int cur = 0, pre = 0;
        fill(dp[cur][0], dp[cur][maxm], INF);
        dp[cur][l][r] = 0;

        for(int now = 1; now <= n; ++now)
        {
            scanf("%d", &pos);
            pre = cur;
            cur = cur^1;
            fill(dp[cur][0], dp[cur][maxm], INF);
            for(int i = 0; i < maxm; ++i)
            {
                for(int j = 0; j < maxm; ++j)
                {
                    if(dp[pre][i][j] == INF)
                        continue;
                    for(int k = pos; k < pos + 9 && k < maxm; k++)
                    {
                        dp[cur][k][j] = min(dp[cur][k][j], dp[pre][i][j] + msqrt[abs(i-k)]);
                    }
                    for(int k = pos; k > pos - 9 && k >= 0; k--)
                    {
                        dp[cur][i][k] = min(dp[cur][i][k], dp[pre][i][j] + msqrt[abs(j-k)]);
                    }
                }
            }
        }
        int res = INF;
        for(int i = 0; i < maxm; ++i)
        {
            for(int j = 0; j < maxm; ++j)
            {
                res = min(res, dp[cur][i][j]);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

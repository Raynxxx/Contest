/*
** LA 6042 Bee Tower
** Created by Rayn @@ 2014/07/21
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 55;
const int INF = 0x3F3F3F3F;

int N, H, W, maxh;
int pos[55], high[55];
int dp[2][55][510];
int vis[2][55][510];

int Solve(int dir, int id, int p)
{
    if(high[id] <= H)
        return 0;
    int add = 1;
    if(dir == 0)
        add = -1;

    int j = id + add;
    if(j < 0 || j >= N)
        return INF;

    if(high[j] == maxh)
        return INF;
    if(high[id] - high[j] > H)
        return INF;

    if(vis[dir][id][p] == 1)
        return dp[dir][id][p];
    vis[dir][id][p] = 1;

    int res = INF;
    for(int k = 1; k <= W; ++k)
    {
        int nowp = p + add*k;
        int cost = abs(pos[j] - nowp) * high[j];
        res = min(res, Solve(dir, j, nowp)+cost);
    }
    dp[dir][id][p] = res;
    return res;
}
int main()
{
#ifdef HotWhite
    freopen("in.txt", "r", stdin);
#endif
    int t, cases = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%d", &N, &H, &W);
        maxh = 0;
        for(int i = 0; i < N; ++i)
        {
            scanf("%d%d", &pos[i], &high[i]);
            maxh = max(maxh, high[i]);
        }
        int res = INF;
        memset(vis, 0, sizeof(vis));
		for(int i = 0; i < N; ++i)
        {
            if(high[i] == maxh)
            {
                res = min(res, Solve(1, i, pos[i]));
                res = min(res, Solve(0, i, pos[i]));
            }
		}
		printf("Case #%d: ", ++cases);
		if(res >= INF)
            printf("-1\n");
		else
            printf("%d\n", res);
    }
    return 0;
}

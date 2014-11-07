/*
** HDU 5045 Contest
** Created by Rayn @@ 2014/09/27
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
typedef long long LL;

const int MAXN = 10;
const int MAXM = 1010;
const int INF = 0x3F3F3F3F;

int n, m;
double dp[MAXM][1<<10];
bool vis[MAXM][1<<10];
double p[MAXN][MAXM];

double Gao(int id, int s)
{
    if(s == ((1 << n) - 1)) s = 0;
    if(vis[id][s]) return dp[id][s];
    vis[id][s] = true;
    dp[id][s] = 0;
    if(id == m) return dp[id][s];
    for(int i = 0; i < n; ++i) {
        if(s & (1 << i)) continue;
        int news = s | (1 << i);
        dp[id][s] = max(dp[id][s], (1 - p[i][id])*Gao(id+1, news) + p[i][id] * (Gao(id+1, news) + 1));
    }
    return dp[id][s];
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%lf", &p[i][j]);
            }
        }
        memset(vis, false, sizeof(vis));
        printf("Case #%d: %.5f\n", ++cases, Gao(0, 0));
    }
    return 0;
}

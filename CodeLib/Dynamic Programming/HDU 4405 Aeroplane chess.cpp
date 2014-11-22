/*
** HDU 4405 Aeroplane chess
** Created by Rayn @@ 2014/09/19
*/
#include <map>
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

const int MAXN = 100010;
const int MAXM = 1010;

bool vis[MAXN];
double dp[MAXN];
map<int, vector<int> > G;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0) break;
        G.clear();
        memset(dp, 0, sizeof(dp));
        memset(vis, false, sizeof(vis));
        while(m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[y].push_back(x);
        }
        vector<int>::iterator it;
        for(it = G[n].begin(); it != G[n].end(); ++it) {
            dp[*it] = 0;
            vis[*it] = true;
        }
        for(int i = n - 1; i >= 0; --i) {
            if(!vis[i]) {
                dp[i] += 1;
                for(int j = i + 1; j <= i + 6; ++j) {
                    dp[i] += dp[j] / 6;
                }
                vis[i] = true;
            }
            vector<int>::iterator it;
            for(it = G[i].begin(); it != G[i].end(); ++it) {
                dp[*it] = dp[i];
                vis[*it] = true;
            }
        }
        printf("%.4f\n", dp[0]);
    }
    return 0;
}

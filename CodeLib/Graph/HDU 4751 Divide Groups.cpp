/*
** HDU 4751 Divide Groups
** Created by Rayn @@ 2014/09/24
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 110;
const int INF = 0x3F3F3F3F;

int n;
int G[MAXN][MAXN];
int group[MAXN];

bool bfs(int s)
{
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 1; i <= n; ++i) {
            if(i == u || (G[i][u] && G[u][i])) continue;
            if(group[i] == -1) {
                group[i] = group[u]^1;
                q.push(i);
            } else if(group[i] == group[u]) {
                return false;
            }
        }
    }
    return true;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) != EOF)
    {
        memset(G, 0, sizeof(G));
        memset(group, -1, sizeof(group));

        for(int i = 1; i <= n; ++i) {
            int id;
            while(scanf("%d", &id) && id) {
                G[i][id] = 1;
            }
        }
        bool flag = true;
        for(int i = 1; i <= n; ++i) {
            if(group[i] == -1) {
                group[i] = 0;
                if(!bfs(i)) {
                    flag = false;
                    break;
                }
            }
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}

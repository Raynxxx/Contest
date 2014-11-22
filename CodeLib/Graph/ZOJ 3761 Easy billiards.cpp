/*
** ZOJ 3761 Easy billiards
** Created by Rayn @@ 2014/08/26
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 2005;
const int INF = 0x3F3F3F3F;

struct Node
{
    int x, y;
    int d;
};

int N, cnt;
Node ball[MAXN];
Node mov[MAXN];
bool vis[MAXN];
vector<int> G[MAXN];

void dfs(int u)
{
    vis[u] = true;
    for(int i = 0; i < (int) G[u].size(); ++i) {
        int v = G[u][i];
        if(!vis[v]) {
            dfs(v);
            mov[cnt] = ball[v];
            if(ball[u].y == ball[v].y && ball[u].x < ball[v].x) {
                mov[cnt].d = 1;
            } else if(ball[u].y == ball[v].y && ball[u].x > ball[v].x) {
                mov[cnt].d = 2;
            } else if(ball[u].x == ball[v].x && ball[u].y > ball[v].y) {
                mov[cnt].d = 3;
            } else if(ball[u].x == ball[v].x && ball[u].y < ball[v].y) {
                mov[cnt].d = 4;
            }
            ++cnt;
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i) {
            scanf("%d%d", &ball[i].x, &ball[i].y);
            G[i].clear();
        }
        for(int i = 1; i <= N; ++i) {
            for(int j = i+1; j <= N; ++j) {
                if(ball[i].x == ball[j].x || ball[i].y == ball[j].y) {
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
            }
        }
        int ret = 0;
        cnt = 0;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= N; ++i) {
            if(!vis[i]) {
                ret++;
                dfs(i);
            }
        }
        printf("%d\n", ret);
        for(int i = 0; i < cnt; ++i) {
            printf("(%d, %d) ", mov[i].x, mov[i].y);
            switch(mov[i].d) {
                case 1: puts("LEFT"); break;
                case 2: puts("RIGHT"); break;
                case 3: puts("UP"); break;
                case 4: puts("DOWN"); break;
            }
        }
    }
    return 0;
}


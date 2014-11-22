/*
** HDU 1102 Constructing Roads
** Created by Rayn @@ 2014/05/04
** 最小生成树Prim
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 110;
const int INF = 0x3f3f3f3f;

int N, Q, ans;
int maps[MAX][MAX], vis[MAX], dis[MAX];

void Prim()
{
    int i, j, k;
    for(i=1; i<=N; ++i)
    {
        dis[i] = maps[1][i];
        vis[i] = 0;
    }
    dis[1] = 0;
    vis[1] = 1;
    for(i=1; i<=N; ++i)
    {
        int tmp = INF;
        for(j=1; j<=N; ++j)
        {
            if(!vis[j] && dis[j] < tmp)
            {
                k = j;
                tmp = dis[j];
            }
        }
        if(tmp == INF)
            return ;
        ans += dis[k];
        vis[k] = 1;
        for(j=1; j<=N; ++j)
        {
            if(!vis[j] && maps[k][j] < dis[j])
                dis[j] = maps[k][j];
        }
    }
}
int main()
{
    int u, v, w;

    while(scanf("%d", &N) != EOF)
    {
        for(int i=1; i<=N; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                scanf("%d", &maps[i][j]);
            }
        }
        scanf("%d", &Q);
        while(Q--)
        {
            scanf("%d%d", &u, &v);
            maps[u][v] = maps[v][u] = 0;
        }
        ans = 0;
        Prim();
        printf("%d\n", ans);
    }
    return 0;
}

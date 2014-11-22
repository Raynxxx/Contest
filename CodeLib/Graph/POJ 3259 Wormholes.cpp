/*
** POJ 3259 Wormholes
** Created by Rayn @@ 2014/05/12
** Bellman-Ford判断负权回路
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 5500;   //数组开小了，果然WA了
const int INF = 0x7f7f7f7f;

struct Edge{
    int u, v, t;
    Edge(int u = 0, int v = 0, int t = 0):
        u(u), v(v), t(t) {}
} path[MAX];

int N, M, W, cnt;
int dis[510];

int Bellman()
{
    int flag = 0;
    memset(dis, INF, sizeof(INF));
    for(int i=1; i<N; ++i)
    {
        flag = 0;
        for(int j=0; j<cnt; j++)
        {
            if(dis[path[j].v] > dis[path[j].u] + path[j].t)
            {
                flag = 1;
                dis[path[j].v] = dis[path[j].u] + path[j].t;
            }
        }
        if(!flag)
            break;
    }
    for(int i=0; i<cnt; ++i)
    {
        if(dis[path[i].v] > dis[path[i].u] + path[i].t)
            return 1;
    }
    return 0;
}
int main()
{
    int T, u, v, t;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &N, &M, &W);

        cnt = 0;
        for(int i=0; i<M; ++i)
        {
            scanf("%d%d%d", &u, &v, &t);
            path[cnt++] = Edge(u, v, t);
            path[cnt++] = Edge(v, u, t);
        }
        for(int i=0; i<W; ++i)
        {
            scanf("%d%d%d", &u, &v, &t);
            path[cnt++] = Edge(u, v, -t);
        }
        if(Bellman())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

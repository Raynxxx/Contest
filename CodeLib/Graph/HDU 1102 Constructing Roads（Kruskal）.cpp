/*
** HDU 1102 Constructing Roads
** Created by Rayn @@ 2014/05/04
** 最小生成树Kruskal
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 110;

struct Edge {
    int u, v;
    int w;
    bool operator < (const Edge& a) const {
        return w < a.w;
    }
} edge[MAX*MAX];

int N, Q, ans, cnt;
int pa[MAX], rnk[MAX];

void MakeSet()
{
    for(int i=0; i<=N; ++i)
    {
        pa[i] = i;
        rnk[i] = 1;
    }
}
inline int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
void AddEdge(int u, int v, int w)
{
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    cnt++;
}
void Kruskal()
{
    sort(edge, edge+cnt);
    for(int i=0; i<cnt; ++i)
    {
        int fx = FindSet(edge[i].u);
        int fy = FindSet(edge[i].v);
        if(fx == fy)
            continue;
        ans += edge[i].w;
        if(rnk[fx] >= rnk[fy])
        {
            pa[fy] = fx;
            rnk[fx] += rnk[fy];
        }
        else
        {
            pa[fx] = fy;
            rnk[fy] += rnk[fx];
        }
    }
}
int main()
{
    int u, v, w;

    while(scanf("%d", &N) != EOF)
    {
        cnt = 0;
        MakeSet();
        for(int i=1; i<=N; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                scanf("%d", &w);
                AddEdge(i, j, w);
            }
        }
        scanf("%d", &Q);
        while(Q--)
        {
            scanf("%d%d", &u, &v);
            int fx = FindSet(u);
            int fy = FindSet(v);
            if(rnk[fx] >= rnk[fy])
            {
                pa[fy] = fx;
                rnk[fx] += rnk[fy];
            }
            else
            {
                pa[fx] = fy;
                rnk[fy] += rnk[fx];
            }
        }
        ans = 0;
        Kruskal();
        printf("%d\n", ans);
    }
    return 0;
}

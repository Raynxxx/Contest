/*
** POJ 2377 Bad Cowtractors
** Created by Rayn @@ 2014/05/27
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXV = 1005;
const int MAXE = 100010;

struct Edge {
    int u, v;
    int val;
    Edge(int u=0, int v=0, int val=0) :
        u(u), v(v), val(val) {}
    bool operator < (const Edge& a) const {
        return val > a.val;
    }
} barn[MAXE];
int pa[MAXV], rnk[MAXV];

void MakeSet()
{
    for(int i=0; i<MAXV; ++i)
    {
        pa[i] = i;
        rnk[i] = 1;
    }
}
int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int Kruskal(int V, int E)
{
    MakeSet();
    sort(barn, barn+E);
    int ans = 0, TreeCnt = 0;
    for(int i = 0; i < E; ++i)
    {
        int px = FindSet(barn[i].u);
        int py = FindSet(barn[i].v);
        if(px == py)
            continue;
        ans += barn[i].val;
        TreeCnt++;
        if(rnk[px] >= rnk[py])
        {
            pa[py] = px;
            rnk[px] += rnk[py];
        }
        else
        {
            pa[px] = py;
            rnk[py] += rnk[px];
        }
    }
    if(TreeCnt == V-1)
        return ans;
    else
        return -1;
}
int main()
{
    int N, M;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        int u, v, w;
        for(int i=0; i<M; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            barn[i] = Edge(u, v, w);
        }
        printf("%d\n", Kruskal(N, M));
    }
	return 0;
}

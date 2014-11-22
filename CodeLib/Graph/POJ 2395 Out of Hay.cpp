/*
** POJ 2395 Out of Hay
** Created by Rayn @@ 2014/05/26
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 2010;
const int MAXM = 10010;

struct Edge {
    int u, v;
    int val;
    Edge(int u=0, int v=0, int val=0) :
        u(u), v(v), val(val) {}
    bool operator < (const Edge& a) const {
        return val < a.val;
    }
} farm[MAXM];

int pa[MAXN], rnk[MAXN];

void MakeSet()
{
    for(int i=1; i<MAXN; ++i)
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
int Kruskal(int E)
{
    MakeSet();
    sort(farm, farm+E);
    int ans = 0;
    for(int i = 0; i < E; ++i)
    {
        int px = FindSet(farm[i].u);
        int py = FindSet(farm[i].v);
        if(px == py)
            continue;
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
        if (farm[i].val > ans)
            ans = farm[i].val;
    }
    return ans;
}
int main()
{
    int N, M, u, v, w;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        for(int i=0; i<M; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            farm[i] = Edge(u, v, w);
        }
        printf("%d\n", Kruskal(M));
    }
	return 0;
}

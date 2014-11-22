/*
** POJ 1258 Agri-Net
** Created by Rayn @@ 2014/05/26
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 105;
const int INF = 0x7FFFFFFF;

struct Edge {
    int u, v;
    int val;
    Edge(int u=0, int v=0, int val=0) :
        u(u), v(v), val(val) {}
    bool operator < (const Edge& a) const {
        return val < a.val;
    }
} farm[MAX*MAX];

int pa[MAX], rnk[MAX];

void MakeSet()
{
    for(int i = 1; i < MAX; ++i)
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
void Kruskal(int n)
{
    MakeSet();
    sort(farm, farm+n);
    int ans = 0;
    for(int i = 0; i < n; ++i)
    {
        int px = FindSet(farm[i].u);
        int py = FindSet(farm[i].v);
        if(px == py)
            continue;
        ans += farm[i].val;
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
    printf("%d\n", ans);
}
int main()
{
    int n, w;
    while(scanf("%d", &n) != EOF && n)
    {
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                scanf("%d", &w);
                farm[cnt++] = Edge(i, j, w);
            }
        }
        Kruskal(cnt);
    }
	return 0;
}

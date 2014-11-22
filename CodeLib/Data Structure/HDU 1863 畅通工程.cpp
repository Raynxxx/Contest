/*
** HDU 1863 ³©Í¨¹¤³Ì
** Created by Rayn @@ 2014/07/02
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;

struct Edge
{
    int u, v, w;
    Edge(int u=0, int v=0, int w=0): u(u), v(v), w(w) {}
    bool operator < (const Edge& rhs) const
    {
        return w < rhs.w;
    }
};

vector<Edge> edge;
int pa[MAXN], rnk[MAXN];
int n, m;

void Init(int n)
{
    edge.clear();
    for(int i = 0; i <= n; ++i)
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
void Kruskal()
{
    sort(edge.begin(), edge.end());
    int ans = 0, road = 0;
    for(int i = 0; i < edge.size(); ++i)
    {
        int px = FindSet(edge[i].u);
        int py = FindSet(edge[i].v);
        if(px != py)
        {
            ans += edge[i].w;
            road++;
            pa[px] = py;
        }
    }
    //printf("road: %d\n", road);
    if(road < m-1)
        printf("?\n");
    else
        printf("%d\n", ans);
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int u, v, w;
    while(scanf("%d%d", &n, &m) != EOF && n)
    {
        Init(n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            edge.push_back(Edge(u, v, w));
        }
        Kruskal();
    }
    return 0;
}

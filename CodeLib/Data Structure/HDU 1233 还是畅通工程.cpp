/*
** HDU 1233 还是畅通工程
** Created by Rayn @@ 2014/07/02
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct Edge
{
    int u, v, w;
    Edge(int u=0, int v=0, int w=0): u(u), v(v), w(w) {}
    bool operator < (const Edge& rhs) const
    {
        return w < rhs.w;
    }
};

int pa[MAXN], rnk[MAXN];
vector<Edge> edge;

void Init(int n)
{
    edge.clear();
    for(int i = 0; i <= n; ++i)
    {
        pa[i] = i;
        rnk[i] = 1;
    }
}
void AddEdge(int u, int v, int w)
{
    edge.push_back(Edge(u, v, w));
}
int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int Kruskal(int E)
{
    int ans = 0;
    sort(edge.begin(), edge.end());
    for(int i = 0; i < E; ++i)
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
    return ans;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    int a, b, d;
    while(scanf("%d", &n) != EOF && n)
    {
        Init(n);
        for(int i = 0; i < (n*(n-1))/2; ++i)
        {
            scanf("%d%d%d", &a, &b, &d);
            AddEdge(a, b, d);
            //AddEdge(b, a, d);
        }
        printf("%d\n", Kruskal(edge.size()));
    }
    return 0;
}

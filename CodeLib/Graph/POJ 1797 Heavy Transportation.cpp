/*
** POJ 1797 Heavy Transportation
** Created by Rayn @@ 2014/07/08
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 0x3F3F3F3F;
const int MAXN = 1010;
const int MAXM = MAXN*MAXN;

struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int u, int  v, int w): u(u), v(v), w(w) {}
    bool operator < (const Edge& rhs) const
    {
        return w > rhs.w;
    }
    void Read()
    {
        scanf("%d%d%d", &u, &v, &w);
    }
} edge[MAXM];

int n, m;
int pa[MAXN];

void Init()
{
    for(int i = 0; i < MAXN; ++i)
        pa[i] = i;
}
int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int Kruskal()
{
    sort(edge, edge+m);
    int ans = INF, cnt = 0;
    for(int i = 0; i < m && cnt < n-1; ++i)
    {
        int fx = FindSet(edge[i].u);
        int fy = FindSet(edge[i].v);
        if(fx != fy)
        {
            cnt++;
            ans = min(ans, edge[i].w);
            pa[fx] = fy;
        }
        if(FindSet(1) == FindSet(n))
            break;
    }
    return ans;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, cases = 0;
    bool first = false;

    scanf("%d", &t);
    while(t--)
    {
        if(first)
            printf("\n");
        else
            first = true;

        Init();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i)
        {
            edge[i].Read();
        }
        printf("Scenario #%d:\n", ++cases);
        printf("%d\n", Kruskal());
    }
    return 0;
}

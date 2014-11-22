/*
** HDU 1845 Jimmy¡¯s Assignment
** Created by Rayn @@ 2014/07/20
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 7510;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int n;
    bool used[MAXN];
    int link[MAXN];
    vector<Edge> edge;
    vector<int> G[MAXN];

    void Init(int n)
    {
        this->n = n;
        for(int i = 0; i <= n; ++i)
            G[i].clear();
        edge.clear();
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        int m = edge.size();
        G[from].push_back(m-1);
    }
    int MaxMatch()
    {
        int sum = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= n; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i))
                sum++;
        }
        return sum;
    }
    bool Find(int u)
    {
        for(int i = 0; i < (int) G[u].size(); ++i)
        {
            int v = edge[G[u][i]].to;
            if(!used[v])
            {
                used[v] = true;
                if(link[v] == -1 || Find(link[v]))
                {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
};

Hungarian Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, n;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        Solver.Init(n*3/2);
        for(int i = 0; i < n*3/2; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            Solver.AddEdge(a, b, 1);
            Solver.AddEdge(b, a, 1);
        }
        printf("%d\n", Solver.MaxMatch()/2);
    }
    return 0;
}
#include<stdio.h>
int main()
{
    int t,n,i,a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=1;i<=n/2*3;i++)
            scanf("%d%d",&a,&b);
        printf("%d\n",n/2);
    }
    return 0;
}

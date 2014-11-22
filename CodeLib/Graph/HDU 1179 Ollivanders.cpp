/*
** HDU 1179 Ollivanders: Makers of Fine Wands since 382 BC.
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int n, m;
    vector<Edge> edge;
    vector<int> G[MAXN];
    int link[MAXN];
    bool used[MAXN];

    void Init(int n)
    {
        this->n = n;
        for(int i = 0; i <= n; ++i)
        {
            G[i].clear();
            G[i].reserve(MAXN);
        }
        edge.clear();
        edge.reserve(MAXN);
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        m = edge.size();
        G[from].push_back(m-1);
    }
    bool Find(int u)
    {
        int s = G[u].size();
        for(int i = 0; i < s; ++i)
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
    int MaxMatch()
    {
        int cnt = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= n; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i)) {
                cnt++;
            }
        }
        return cnt;
    }
};

Hungarian Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, m, k, b;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Solver.Init(m);
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d", &k);
            for(int j = 0; j < k; ++j)
            {
                scanf("%d", &b);
                Solver.AddEdge(i, b, 1);
            }
        }
        printf("%d\n", Solver.MaxMatch());
    }
    return 0;
}

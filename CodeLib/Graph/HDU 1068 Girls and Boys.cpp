/*
** HDU 1068 Girls and Boys
** Created by Rayn @@ 2014/07/16
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct HunGarian
{
    int n, m;
    vector<Edge> edge;
    vector<int> G[MAXN];
    int link[MAXN];
    bool check[MAXN];

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
        int m = G[u].size();
        for(int i = 0; i < m; ++i)
        {
            int v = edge[G[u][i]].to;
            if(!check[v])
            {
                check[v] = true;
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
        for(int i = 0; i < n; ++i)
        {
            memset(check, false, sizeof(check));
            if(Find(i)) {
                cnt++;
            }
        }
        return cnt;
    }
};

HunGarian solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n;
    while(scanf("%d", &n) != EOF && n)
    {
        solver.Init(n);
        for(int i = 0; i < n; ++i)
        {
            int id, num, b;
            scanf("%d: (%d)", &id, &num);
            for(int j = 0; j < num; ++j)
            {
                scanf("%d", &b);
                solver.AddEdge(id, b, 1);
            }
        }
        printf("%d\n", n - solver.MaxMatch()/2);
    }
    return 0;
}

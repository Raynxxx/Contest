/*
** HDU 1151 Air Raid
** Created by Rayn @@ 2014/07/16
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 150;

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
    bool used[MAXN];
    int link[MAXN];

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
    int t, n, k;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &k);
        Solver.Init(n);
        for(int i = 0; i < k; ++i)
        {
            int s, e;
            scanf("%d%d", &s, &e);
            Solver.AddEdge(s, e, 1);
        }
        printf("%d\n", n - Solver.MaxMatch());
    }
    return 0;
}

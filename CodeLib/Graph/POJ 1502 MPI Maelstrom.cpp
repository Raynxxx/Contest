/*
** POJ 1502 MPI Maelstrom
** Created by Rayn @@ 2014/07/10
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 210;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to, dist;
    Edge() {}
    Edge(int from, int to, int dist):
        from(from), to(to), dist(dist) {}
};

struct Heap
{
    int u, d;
    Heap() {}
    Heap(int u, int d): u(u), d(d) {}
    bool operator < (const Heap& rhs) const
    {
        return d > rhs.d;
    }
};
struct Dijkstra
{
    int V, E;
    vector<Edge> edge;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int dis[MAXN];

    Dijkstra(int n = 0)
    {
        this->V = n;
        for(int i = 0; i <= n; ++i)
        {
            G[i].clear();
            G[i].reserve(MAXN);
        }
        edge.clear();
        edge.reserve(MAXN*MAXN);
    }
    void AddEdge(int from, int to, int dist)
    {
        edge.push_back(Edge(from, to, dist));
        E = edge.size();
        G[from].push_back(E-1);
    }
    void Work(int src)
    {
        memset(vis, false, sizeof(vis));
        for(int i = 0; i <= V; ++i)
        {
            dis[i] = (i == src)? 0 : INF;
        }
        priority_queue<Heap> q;
        q.push(Heap(src, 0));
        while(!q.empty())
        {
            int u = q.top().u;
            q.pop();
            if(vis[u])
                continue;
            vis[u] = true;
            for(int i = 0; i < (int) G[u].size(); ++i)
            {
                Edge& e = edge[G[u][i]];
                if(dis[e.to] > dis[u] + e.dist)
                {
                    dis[e.to] = dis[u] + e.dist;
                    q.push(Heap(e.to, dis[e.to]));
                }
            }
        }
    }
    int GetAnswer(int dest)
    {
        return dis[dest];
    }
};
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, d;
    char w[20];
    while(scanf("%d%*c", &n) != EOF)
    {
        Dijkstra solver(n);
        for(int i = 2; i <= n; ++i)
        {
            for(int j = 1; j < i; ++j)
            {
                scanf("%s", w);
                if(w[0] == 'x')
                {
                    continue;
                }
                else
                {
                    d = 0;
                    for(int i = 0, len = strlen(w); i < len; ++i)
                    {
                        d = d * 10 + (w[i] - '0');
                    }
                }
                //printf("road:  %d %d %d\n", i, j, d);
                solver.AddEdge(i, j, d);
                solver.AddEdge(j, i, d);
            }
        }
        solver.Work(1);
        int maxroad = -1;
        for(int i = 1; i <= n; ++i)
        {
            //printf("dis[%d]: %d\n", i, solver.GetAnswer(i));
            maxroad = max(maxroad, solver.GetAnswer(i));
        }
        printf("%d\n", maxroad);
    }
    return 0;
}

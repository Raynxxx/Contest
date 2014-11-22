/*
** POJ 3268 Silver Cow Party
** Created by Rayn @@ 2014/07/10
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
const int MAXM = 200010;
const int INF = 0x3F3F3F3F;

struct Edge{
    int from, to, dist;
    Edge() {}
    Edge(int from, int to, int dist): from(from), to(to), dist(dist) {}
};

struct HeapNode
{
    int u, d;
    HeapNode() {}
    HeapNode(int u, int d): u(u), d(d) {}
    bool operator < (const HeapNode& rhs) const
    {
        return d > rhs.d;
    }
};

struct Dijkstra
{
    int n, m;
    vector<Edge> edge;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int dis[MAXN];

    Dijkstra(int n = 0)
    {
        this->n = n;
        for(int i = 0; i < MAXN; ++i)
            G[i].clear();
        edge.clear();
    }
    void AddEdge(int from, int to, int dist)
    {
        edge.push_back(Edge(from, to, dist));
        m = edge.size();
        G[from].push_back(m-1);
    }
    void Work(int s)
    {
        priority_queue<HeapNode> q;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; ++i)
        {
            dis[i] = (i == s)? 0 : INF;
        }
        q.push(HeapNode(s, 0));
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
                    q.push(HeapNode(e.to, dis[e.to]));
                }
            }
        }
    }
    int GetDis(int dest)
    {
        return dis[dest];
    }
};

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, m, x;
    int u, v, w;

    while(scanf("%d%d%d", &n, &m, &x) != EOF)
    {
        Dijkstra come(n), backing(n);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            come.AddEdge(u, v, w);
            backing.AddEdge(v, u, w);
        }
        come.Work(x);
        backing.Work(x);
        int ans = -1;
        for(int i = 1; i <= n; ++i)
        {
            if(come.GetDis(i) + backing.GetDis(i) > ans)
            {
                ans = come.GetDis(i) + backing.GetDis(i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

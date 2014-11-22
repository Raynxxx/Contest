/*
** HDU 3790 最短路径问题
** Created by Rayn @@ 2014/06/30
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to, dist, cost;
    Edge(int u=0, int v=0, int d=0, int c=0):
        from(u), to(v), dist(d), cost(c) {}
};

struct HeapNode
{
    int u;
    int dist, cost;
    HeapNode(int u=0, int d=0, int c=0):
        u(u), dist(d), cost(c) {}
    bool operator < (const HeapNode& rhs) const
    {
        return dist > rhs.dist || (dist == rhs.dist && cost > rhs.cost);
    }
};

int V, E;
vector<Edge> edge;
vector<int> G[MAXN];
bool vis[MAXN];
int dis[MAXN], cost[MAXN];

void Init(int n)
{
    V = n;
    for(int i = 0; i < n; ++i)
        G[i].clear();
    edge.clear();
}
void AddEdge(int from, int to, int dist, int cost)
{
    edge.push_back(Edge(from, to, dist, cost));
    E = edge.size();
    G[from].push_back(E-1);
}
void Dijkstra(int s)
{
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i <= V; ++i)
    {
        dis[i] = cost[i] = (i == s)? 0 : INF;
    }
    priority_queue<HeapNode> q;
    q.push(HeapNode(s, 0, 0));
    while(!q.empty())
    {
        HeapNode now = q.top();
        q.pop();
        int u = now.u;
        if(vis[u])
            continue;
        vis[u] = true;
        for(int i = 0; i < G[u].size(); ++i)
        {
            Edge& e = edge[G[u][i]];
            if(dis[e.to] > dis[u] + e.dist)
            {
                dis[e.to] = dis[u] + e.dist;
                cost[e.to] = cost[u] + e.cost;
                q.push(HeapNode(e.to, dis[e.to], cost[e.to]));
            }
            else if(dis[e.to] == dis[u] + e.dist)
            {
                if(cost[e.to] > cost[u] + e.cost)
                    cost[e.to] = cost[u] + e.cost;
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, m, s, t;
    int a, b, d, p;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(!n && !m)
            break;

        Init(n+1);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d%d%d", &a, &b, &d, &p);
            AddEdge(a, b, d, p);
            AddEdge(b, a, d, p);
        }
        scanf("%d%d", &s, &t);
        Dijkstra(s);
        printf("%d %d\n", dis[t], cost[t]);
    }
    return 0;
}

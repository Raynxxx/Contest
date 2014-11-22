/*
** HDU 1874 畅通工程续
** Created by Rayn @@ 2014/07/02
*/
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 210;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int u, v, dis;
    Edge() {}
    Edge(int u, int v, int d): u(u), v(v), dis(d) {}
};
struct HeapNode
{
    int u, dis;
    HeapNode(int u, int d): u(u), dis(d) {}
    bool operator < (const HeapNode& rhs) const
    {
        return dis > rhs.dis;
    }
};

int V, E;
int dis[MAXN];
bool vis[MAXN];
vector<Edge> edge;
vector<int> G[MAXN];

void Init(int n)
{
    V = n;
    for(int i = 0; i < MAXN; ++i)
        G[i].clear();
    edge.clear();
}
void AddEdge(int from, int to, int dis)
{
    edge.push_back(Edge(from, to, dis));
    E = edge.size();
    G[from].push_back(E-1);
}
int Dijkstra(int s, int dest)
{
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < V; ++i)
    {
        dis[i] = (i == s)? 0 : INF;
    }
    priority_queue<HeapNode> q;
    q.push(HeapNode(s, 0));
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
            if(dis[e.v] > dis[u] + e.dis)
            {
                dis[e.v] = dis[u] + e.dis;
                q.push(HeapNode(e.v, dis[e.v]));
            }
        }
    }
    if(dis[dest] == INF)
        return -1;
    return dis[dest];
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, m, s, t;
    int u, v, w;
    while(scanf("%d%d", &n, &m) != EOF && n)
    {
        Init(n);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w);
            AddEdge(v, u, w);
        }
        scanf("%d%d", &s, &t);
        printf("%d\n", Dijkstra(s, t));
    }
    return 0;
}

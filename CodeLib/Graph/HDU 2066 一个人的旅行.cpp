/*
** HDU 2066 一个人的旅行
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
    int from, to, time;
    Edge(int u=0, int v=0, int t=0): from(u), to(v), time(t) {}
};
struct HeapNode
{
    int u, time;
    HeapNode(int u=0, int t=0): u(u), time(t) {}
    bool operator < (const HeapNode& rhs) const
    {
        return time > rhs.time;
    }
};

vector<Edge> edge;
vector<int> G[MAXN];
int V, E;
bool vis[MAXN];
int dis[MAXN];
int Sarr[MAXN], Darr[MAXN];

void Init(int n)
{
    V = n;
    for(int i = 0; i < n; ++i)
        G[i].clear();
    edge.clear();
}
void AddEdge(int from, int to, int time)
{
    edge.push_back(Edge(from, to, time));
    E = edge.size();
    G[from].push_back(E-1);
    //printf("G[%d].size = %d\n", from, G[from].size());
}
void Dijkstra(int s)
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
        HeapNode now = q.top(); q.pop();
        int u = now.u;
        if(vis[u])
            continue;
        vis[u] = true;
        for(int i = 0; i < G[u].size(); ++i)
        {
            Edge& e = edge[G[u][i]];
            if(dis[e.to] > dis[u] + e.time)
            {
                dis[e.to] = dis[u] + e.time;
                q.push(HeapNode(e.to, dis[e.to]));
            }
        }
    }

}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, S, D;
    int a, b, time;

    while(scanf("%d%d%d", &T, &S, &D) != EOF)
    {
        int n = 0;
        Init(MAXN);
        for(int i = 0; i < T; ++i)
        {
            scanf("%d%d%d", &a, &b, &time);
            AddEdge(a, b, time);
            AddEdge(b, a, time);
            n = max(n, max(a, b));
        }
        V = n + 1;
        for(int i = 0; i < S; ++i)
            scanf("%d", &Sarr[i]);
        for(int i = 0; i < D; ++i)
            scanf("%d", &Darr[i]);

        int ans = INF;
        for(int i = 0; i < S; ++i)
        {
            Dijkstra(Sarr[i]);
            int Min = INF;
            for(int j = 0; j < D; ++j)
            {
                //printf("%d\n", dis[Darr[j]]);
                Min = min(dis[Darr[j]], Min);
            }
            ans = min(ans, Min);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
** POJ 1511 Invitation Cards
** Created by Rayn @@ 2014/07/13
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL INF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 1000010;

struct Edge
{
    int from, to;
    long long dist;
    int next;
    Edge() {}
    Edge(int from, int to, long long dist, int next):
        from(from), to(to), dist(dist), next(next) {}
};
struct HeapNode
{
    int u;
    long long d;
    HeapNode() {}
    HeapNode(int u, long long d): u(u), d(d) {}
    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};

struct Dijkstra
{
    int n, m, sz;
    int head[MAXN];
    Edge edge[MAXN];
    bool vis[MAXN];
    long long dis[MAXN];

    void Init(int n, int m)
    {
        this->n = n;
        this->m = m;
        sz = 0;
        memset(head, -1, sizeof(head));
        memset(edge, 0, sizeof(edge));
    }
    void AddEdge(int from, int to, LL dist)
    {
        edge[sz] = Edge(from, to, dist, head[from]);
        head[from] = sz++;
    }
    void Solve(int s)
    {
        priority_queue<HeapNode> que;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; ++i)
        {
            dis[i] = (i == s)? 0 : INF;
        }
        que.push(HeapNode(s, 0));
        while(!que.empty())
        {
            int u = que.top().u;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = true;
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                int v = edge[i].to;
                if(dis[v] > dis[u] + edge[i].dist)
                {
                    dis[v] = dis[u] + edge[i].dist;
                    que.push(HeapNode(v, dis[v]));
                }
            }
        }
    }
};

Dijkstra Come, Back;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int T, P, Q;
    int u, v;
    LL w;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &P, &Q);
        Come.Init(P, Q);
        Back.Init(P, Q);
        for(int i = 0; i < Q; ++i)
        {
            scanf("%d%d%lld", &u, &v, &w);
            Come.AddEdge(u, v, w);
            Back.AddEdge(v, u, w);
        }
        Come.Solve(1);
        Back.Solve(1);
        long long ans = 0;
        for(int i = 1; i <= P; ++i)
        {
            ans += Come.dis[i] + Back.dis[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}

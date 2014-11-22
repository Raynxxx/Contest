/*
** ZOJ 2314 Reactor Cooling
** Created by Rayn @@ 2014/08/10
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 250;
const int maxm = 250*250*2;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to, cap, flow;
    int next;

    Edge() {}
    Edge(int from, int to, int cap, int flow, int next):
        from(from), to(to), cap(cap), flow(flow), next(next) {}
};

struct LimitFlow
{
    int n, m, sz;
    int source, sink;
    int b[maxm], c[maxm], limit[maxn];
    int d[maxn], head[maxn], cur[maxn];
    bool vis[maxn];
    Edge edge[maxm];

    void Init(int n, int m)
    {
        this->n = n;
        this->m = m;
        sz = 0;
        source = 0;
        sink = n + 1;
        memset(head, -1, sizeof(head));
        memset(limit, 0, sizeof(limit));
    }
    void AddEdge(int from, int to, int cap, int flow)
    {
        edge[sz] = Edge(from, to, cap, flow, head[from]);
        head[from] = sz++;
        cur[from] = head[from];
    }
    void ReadGraph()
    {
        for(int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d%d%d%d", &u, &v, &b[i], &c[i]);
            AddEdge(u, v, c[i]-b[i], 0);
            AddEdge(v, u, 0, 0);
            limit[u] -= b[i];
            limit[v] += b[i];
        }
    }
    void Work()
    {
        int in = 0;
        for(int i = 1; i <= n; ++i)
        {
            if (limit[i] > 0) {
                AddEdge(source, i, limit[i], 0);
                AddEdge(i, source, 0, 0);
                in += limit[i];
            } else if (limit[i] < 0) {
                AddEdge(i, sink, -limit[i], 0);
                AddEdge(sink, i, 0, 0);
            }
        }
        if(MaxFlow(source, sink) != in)
        {
            printf("NO\n");
            return ;
        }
        printf("YES\n");
        for(int i = 0; i < m; ++i)
        {
            printf("%d\n", edge[2*i].flow + b[i]);
        }
    }
    bool bfs()
    {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(source);
        vis[source] = true;
        d[source] = 0;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                int v = edge[i].to;
                int w = edge[i].cap - edge[i].flow;
                if(!vis[v] && w > 0)
                {
                    vis[v] = true;
                    Q.push(v);
                    d[v] = d[u] + 1;
                }
            }
        }
        return vis[sink];
    }
    int dfs(int u, int a)
    {
        if(u == sink || a == 0)
            return a;
        int flow = 0, f;
        for(int& i = cur[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            int w = edge[i].cap - edge[i].flow;
            if(w > 0 && d[v] == d[u] + 1 && (f = dfs(v, min(a, w))) > 0)
            {
                edge[i].flow += f;
                edge[i^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0)
                    break;
            }
        }
        return flow;
    }
    int MaxFlow(int st, int ed)
    {
        int flow = 0;
        while(bfs())
        {
            memcpy(cur, head, sizeof(head));
            flow += dfs(st, INF);
        }
        return flow;
    }
};


LimitFlow Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, N, M;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &M);
        Solver.Init(N, M);
        Solver.ReadGraph();
        Solver.Work();
        if(T > 0)
            puts("");
    }
    return 0;
}

/*
** HDU 4940 Destroy Transportation system
** Created by Rayn @@ 2014/08/15
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
using namespace std;
const int MAXN = 210;
const int MAXM = 5010*5;
const int INF = 0x3F3F3F3F;

struct Dinic
{
    struct Edge
    {
        int from, to, cap, flow;
        int next;
        Edge() {}
        Edge(int from, int to, int cap, int flow, int next):
            from(from), to(to), cap(cap), flow(flow), next(next) {}
    };

    int n, m;
    int s, t;
    bool vis[MAXN];
    int dis[MAXN];
    int head[MAXN];
    int cur[MAXN];
    Edge edge[MAXM];

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to, int cap)
    {
        edge[m] = Edge(from, to, cap, 0, head[from]);
        head[from] = m++;
    }
    bool bfs()
    {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        dis[s] = 0;
        vis[s] = true;
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
                    dis[v] = dis[u] + 1;
                    Q.push(v);
                }
            }
        }
        return vis[t];
    }
    int dfs(int u, int a)
    {
        if(u == t || a == 0)
            return a;
        int flow = 0, f;
        for(int& i = cur[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            int w = edge[i].cap - edge[i].flow;
            if(dis[v] == dis[u] + 1 && (f = dfs(v, min(a, w))) > 0)
            {
                edge[i].flow += f;
                edge[i^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s, int t)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        while(bfs())
        {
            memcpy(cur, head, sizeof(head));
            flow += dfs(s, INF);
        }
        return flow;
    }
};

Dinic Solver;
int limit[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, cases = 0, n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        Solver.Init(n);
        memset(limit, 0, sizeof(limit));
        for(int i = 0; i < m; ++i)
        {
            int u, v, d, b;
            scanf("%d%d%d%d", &u, &v, &d, &b);
            limit[u] -= d;
            limit[v] += d;
            Solver.AddEdge(u, v, b);
            Solver.AddEdge(v, u, 0);
        }
        int in = 0;
        int s = 0, t = n+1;
        for(int i = 1; i <= n; ++i)
        {
            if(limit[i] > 0) {
                in += limit[i];
                Solver.AddEdge(s, i, limit[i]);
                Solver.AddEdge(i, s, 0);
            } else if(limit[i] < 0) {
                Solver.AddEdge(i, t, -limit[i]);
                Solver.AddEdge(t, i, 0);
            }
        }
        printf("Case #%d: ", ++cases);
        if(Solver.MaxFlow(s, t) == in) {
            printf("happy\n");
        } else {
            printf("unhappy\n");
        }
    }
    return 0;
}

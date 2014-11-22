/*
** ZOJ 3792 Romantic Value
** Created by Rayn @@ 2014/08/13
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int SIZE = 2000;
const int MAXN = 64;
const int MAXM = 10240;

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
    int head[MAXN];
    int cur[MAXN];
    bool vis[MAXN];
    int dis[MAXN];
    Edge edge[MAXM];

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(head));
        memset(cur, -1, sizeof(cur));
    }
    void AddEdge(int u, int v, int cap)
    {
        edge[m] = Edge(u, v, cap, 0, head[u]);
        head[u] = m++;
        edge[m] = Edge(v, u, 0, 0, head[v]);
        head[v] = m++;
    }
    bool bfs()
    {
        memset(vis, 0, sizeof(vis));
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
        if(u == t || a == 0) return a;
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
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T;
    int n, m, p, q;
    int u, v, c;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d%d", &n, &m, &p, &q);
        Solver.Init(n);
        int sum = 0;
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &u, &v, &c);
            sum += c;
            Solver.AddEdge(u, v, c * SIZE + 1);
            Solver.AddEdge(v, u, c * SIZE + 1);
        }
        int maxflow = Solver.MaxFlow(p, q);
        int road = maxflow % SIZE;
        int mincut = maxflow / SIZE;
        if(road == 0)
            printf("Inf\n");
        else
            printf("%.2f\n", 1.0 * (sum - mincut) / road);
    }
    return 0;
}

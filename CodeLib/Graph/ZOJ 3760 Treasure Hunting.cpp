/*
** ZOJ 3760 Treasure Hunting
** Created by Rayn @@ 2014/08/26
** 340ms Accepted
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 512;
const int MAXM = MAXN * MAXN;

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

    int n, m, s, t;
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
        edge[m] = Edge(to, from, 0, 0, head[to]);
        head[to] = m++;
    }
    bool bfs()
    {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        vis[s] = true;
        dis[s] = 0;
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
            if(dis[v] == dis[u] + 1 && (f = dfs(v, min(a, w)) ) > 0)
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
    LL MaxFlow(int s, int t)
    {
        this->s = s;
        this->t = t;
        LL flow = 0;
        while(bfs())
        {
            memcpy(cur, head, sizeof(head));
            flow += dfs(s, INF);
        }
        return flow;
    }
};

Dinic Network;
int N, P, S, T;
int pos[MAXN], val[MAXN];

inline bool check(int a, int b)
{
    if(((a ^ b) & 1) == 0) return false;
    if(__gcd(a ^ b, P) <= 1)
        return true;
    else
        return false;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &N, &P) != EOF)
    {
        LL sum = 0;
        S = 0, T = N+1;
        Network.Init(N+2);
        for(int i = 1, x, y; i <= N; ++i)
        {
            scanf("%d%d", &x, &y);
            pos[i] = x ^ y;
            val[i] = x & y;
            sum += val[i];
            if(pos[i] & 1) {
                Network.AddEdge(S, i, val[i]);
            } else {
                Network.AddEdge(i, T, val[i]);
            }
        }
        for(int i = 1; i <= N; ++i)
        {
            for(int j = i+1; j <= N; ++j)
            {
                if(check(pos[i], pos[j]))
                {
                    if(pos[i] & 1)
                        Network.AddEdge(i, j, INF);
                    else
                        Network.AddEdge(j, i, INF);
                }
            }
        }
        printf("%lld\n", sum - Network.MaxFlow(S, T));
    }
    return 0;
}


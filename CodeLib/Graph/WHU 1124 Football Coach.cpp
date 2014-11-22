/*
** WHU 1124 Football Coach
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1200;
const int MAXM = MAXN * MAXN * 2;
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

    int n, m, s, t;
    bool vis[MAXN];
    int d[MAXN];
    int head[MAXN];
    int cur[MAXN];
    Edge edge[MAXM];

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(int)*(n+1));
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
        d[s] = 0;
        vis[s] = true;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                Edge& e = edge[i];
                if(!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = true;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x, int a)
    {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            int w = edge[i].cap - edge[i].flow;
            if(d[v] == d[x] + 1 && (f = dfs(v, min(a, w))) > 0)
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
        this->s = s; this->t = t;
        int flow = 0;
        while(bfs())
        {
            memcpy(cur, head, sizeof(head));
            flow += dfs(s, INF);
        }
        return flow;
    }
};

Dinic Network;
int N, M, S, T;
int score[128];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while (scanf("%d%d", &N, &M) != EOF)
    {
        S = 0, T = N+M+1;
        Network.Init(N+M+2);
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &score[i]);
        }
        int Match = M;
        for(int i = 1, a, b; i <= M; ++i) {
            scanf("%d%d", &a, &b);
            if(a == N || b == N) {
                score[N] += 2;
                Match--;
                continue;
            }
            Network.AddEdge(S, i, 2);
            Network.AddEdge(i, M+a, 2);
            Network.AddEdge(i, M+b, 2);
        }
        bool fail = false;
        for(int i = 1; i < N; ++i) {
            if(score[i] >= score[N]) {
                fail = true;
                break;
            }
            Network.AddEdge(M + i, T, score[N]-score[i]-1);
        }
        if(fail) {
            printf("NO\n");
        } else {
            if(Network.MaxFlow(S, T) == 2 * Match) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}

/*
** HDU 4973 A simple brute force problem
** Created by Rayn @@ 2014/08/29
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
const int MAXN = 100;
const int MAXM = MAXN * MAXN * 2;
const int INF = 0x3F3F3F3F;

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    return ret;
}

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
int N, M, S, T, tot;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int test, cases = 0;
    scanf("%d", &test);
    while(test--)
    {
        scanf("%d%d", &N, &M);
        S = 0, T = N+M+1, tot = 0;
        Network.Init(N+M+2);
        for(int i = 1, profit; i <= N; ++i)
        {
            //scanf("%d", &profit);
            profit = nextInt();
            tot += profit;
            Network.AddEdge(S, i, profit);
        }
        for(int i = 1, cost; i <= M; ++i)
        {
            //scanf("%d", &cost);
            cost = nextInt();
            Network.AddEdge(N+i, T, cost);
        }
        for(int i = 1, k; i <= N; ++i)
        {
            //scanf("%d", &k);
            k = nextInt();
            for(int j = 1, id; j <= k; ++j)
            {
                //scanf("%d", &id);
                id = nextInt() + 1;
                Network.AddEdge(i, N+id, INF);
            }
        }
        for(int i = 1, flag; i <= M; ++i)
        {
            for(int j = 1; j <= M; ++j)
            {
                //scanf("%d", &flag);
                flag = nextInt();
                if(flag) {
                    Network.AddEdge(N+i, N+j, INF);
                }
            }
        }
        int MinCut = Network.MaxFlow(S, T);
        printf("Case #%d: %d\n", ++cases, tot - MinCut);
    }
    return 0;
}

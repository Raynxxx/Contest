/*
** HDU 4888 Redraw Beautiful Drawings
** Created by Rayn @@ 2014/08/17
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 0x3F3F3F3F;
const int MAXN = 820;
const int MAXM = MAXN*MAXN;

int N, M, K;
int sumx, sumy;
int row[MAXN], col[MAXN];

class GraphDinic
{
public:
    struct Edge
    {
        int from, to, cap, flow;
        int next;
        Edge() {}
        Edge(int from, int to, int cap, int flow, int next):
            from(from), to(to), cap(cap), flow(flow), next(next) {}
    };

    int n, m, s, t;
    bool flag;
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
    void dfs2(int x, int pre)
    {
        if(flag) return ;
        if(vis[x]) {
            flag = true;
            return ;
        }
        vis[x] = true;
        for(int& i = head[x]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(edge[i].cap - edge[i].flow > 0 && v != pre)
            {
                dfs2(v, x);
            }
        }
        vis[x] = false;
    }
    void Gao(int S, int T)
    {
        if(MaxFlow(S, T) != sumx)
        {
            printf("Impossible\n");
            return ;
        }
        flag = false;
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= N; ++i)
        {
            if(flag)
                break;
            if(!vis[i])
                dfs2(i, -1);
        }
        if(flag) {
            printf("Not Unique\n");
        } else {
            printf("Unique\n");
            int sz = 0;
            for(int i = 1; i <= N; i++)
            {
                for(int j = 1; j <= M; j++)
                {
                    printf("%d%c", edge[sz].flow, (j == M ? '\n' : ' '));
                    sz += 2;
                }
            }
        }
    }
};

GraphDinic Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d%d", &N, &M, &K) != EOF)
    {
        sumx = sumy = 0;
        for(int i = 1; i <= N; ++i)
        {
            scanf("%d", &row[i]);
            sumx += row[i];
        }
        for(int i = 1; i <= M; ++i)
        {
            scanf("%d", &col[i]);
            sumy += col[i];
        }
        if(sumx != sumy)
        {
            printf("Impossible\n");
            continue;
        }
        Solver.Init(N+M+1);
        int S = 0, T = N+M+1;
        for(int i = 1; i <= N; ++i)
        {
            for(int j = 1; j <= M; ++j)
            {
                Solver.AddEdge(i, N+j, K);
            }
        }
        for(int i = 1; i <= N; ++i)
        {
            Solver.AddEdge(S, i, row[i]);
        }
        for(int j = 1; j <= M; ++j)
        {
            Solver.AddEdge(N+j, T, col[j]);
        }
        Solver.Gao(S, T);
    }
    return 0;
}

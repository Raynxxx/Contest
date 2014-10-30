/*
** HDU 4862 Jump
** Created by Rayn @@ 2014/08/16
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
typedef long long LL;
using namespace std;
const int MAXN = 220;
const int MAXM = MAXN*MAXN;
const int INF = 0x3F3F3F3F;

struct MCMF
{
    struct Edge
    {
        int from, to, cap, flow, cost;
        int next;
        Edge() {}
        Edge(int from, int to, int cap, int flow, int cost, int next):
            from(from), to(to), cap(cap), flow(flow), cost(cost), next(next) {}
    };

    int n, m;
    int head[MAXN];
    bool inq[MAXN];
    int dis[MAXN];
    int pre[MAXN];
    int low[MAXN];
    Edge edge[MAXM];

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to, int cap, int cost)
    {
        edge[m] = Edge(from, to, cap, 0, cost, head[from]);
        head[from] = m++;
        edge[m] = Edge(to, from, 0, 0, -cost, head[to]);
        head[to] = m++;
    }
    bool SPFA(int s, int t, int& flow, int& cost)
    {
        memset(inq, false, sizeof(inq));
        memset(dis, INF, sizeof(dis));
        queue<int> Q;
        Q.push(s);
        inq[s] = true;
        dis[s] = 0;
        pre[s] = 0;
        low[s] = INF;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                int v = edge[i].to;
                int w = edge[i].cap - edge[i].flow;
                if(w > 0 && dis[v] > dis[u] + edge[i].cost)
                {
                    dis[v] = dis[u] + edge[i].cost;
                    pre[v] = i;
                    low[v] = min(low[u], w);
                    if(!inq[v])
                    {
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        if(dis[t] == INF)
            return false;
        flow += low[t];
        cost += low[t] * dis[t];
        int u = t;
        while(u != s)
        {
            edge[pre[u]].flow += low[t];
            edge[pre[u]^1].flow -= low[t];
            u = edge[pre[u]].from;
        }
        return true;
    }
    void MinCost(int s, int t, int& flow, int& cost)
    {
        flow = cost = 0;
        while(SPFA(s, t, flow, cost));
    }
};

int n, m, k;
int flow, cost;
int dir[2][2] = {{0, 1}, {1, 0}};
int grid[MAXN][MAXN];
MCMF Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    char buf[15];

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &k);
        Solver.Init(2*n*m+2);
        for(int i = 1; i <= n; ++i)
        {
            scanf("%s", buf + 1);
            for(int j = 1; j <= m; ++j)
            {
                grid[i][j] = buf[j] - '0';
            }
        }
        int S = 0, T = 2*n*m+2;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                Solver.AddEdge(S, (i-1)*m+j, 1, 0);
            }
        }
        Solver.AddEdge(S, 2*n*m+1, k, 0);
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                Solver.AddEdge((i-1)*m+j+n*m, T, 1, 0);
                Solver.AddEdge(2*n*m+1, (i-1)*m+j+n*m, 1, 0);
            }
        }
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                for(int d = 0; d < 2; ++d)
                {
                    int tx = i, ty = j;
                    while(tx + dir[d][0] <= n && ty + dir[d][1] <= m)
                    {
                        tx += dir[d][0];
                        ty += dir[d][1];
                        int f = abs(tx-i) + abs(ty-j) - 1 - (grid[i][j] == grid[tx][ty]? grid[i][j] : 0);
                        Solver.AddEdge((i-1)*m+j, (tx-1)*m+ty+n*m, 1, f);
                    }
                }
            }
        }
        Solver.MinCost(S, T, flow, cost);
        printf("Case %d : ", ++cases);
        if(flow == n*m)
            printf("%d\n", -cost);
        else
            printf("-1\n");
    }
    return 0;
}

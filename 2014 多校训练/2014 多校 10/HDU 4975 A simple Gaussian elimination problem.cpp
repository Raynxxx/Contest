/*
** HDU 4975 A simple Gaussian elimination problem
** Created by Rayn @@ 2014/08/29
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 1024;
const int MAXM = MAXN*MAXN;

int N, M, S, T;
int sumx, sumy;
int row[MAXN], col[MAXN];

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
        int flow = 0;
        while(bfs())
        {
            memcpy(cur, head, sizeof(head));
            flow += dfs(s, INF);
        }
        return flow;
    }
    bool dfs2(int x, int pre)
    {
        int flag = -1;
        vis[x] = true;
        for(int i = head[x]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(v == pre)
                continue;
            if(edge[i].cap > edge[i].flow) {
                if(vis[v]) return true;
                if(dfs2(v, x)) return true;
            }
            if(flag == -1) {
                head[x] = edge[i].next; //删边，因为这条边为0或者走了这条边却没发现环
            } else {
                edge[flag].next = edge[i].next;
            }
            flag = i;
        }
        vis[x] = false;
        return false;
    }
    void gao(int s, int t)
    {
        this->s = s; this->t = t;
        if(MaxFlow(s, t) != sumx)
        {
            printf("So naive!\n");
            return ;
        }
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= N; ++i) {
            if(dfs2(i, -1)) {
                printf("So young!\n");
                return ;
            }
        }
        printf("So simple!\n");
    }
};

Dinic Network;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int Test, cases = 0;
    Test = nextInt();
    while(Test--)
    {
        N = nextInt();
        M = nextInt();
        sumx = sumy = 0;
        for(int i = 1; i <= N; ++i) {
            row[i] = nextInt();
            sumx += row[i];
        }
        for(int i = 1; i <= M; ++i) {
            col[i] = nextInt();
            sumy += col[i];
        }
        printf("Case #%d: ", ++cases);
        if(sumx != sumy) {
            printf("So naive!\n");
            continue;
        }
        S = 0, T = N+M+1;
        Network.Init(N+M+2);
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= M; ++j) {
                Network.AddEdge(i, j+N, 9);
            }
        }
        for(int i = 1; i <= N; ++i) {
            Network.AddEdge(S, i, row[i]);
        }
        for(int j = 1; j <= M; ++j) {
            Network.AddEdge(j+N, T, col[j]);
        }
        Network.gao(S, T);
    }
    return 0;
}

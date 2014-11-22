/*
** HDU 4859 海岸线
** Created by Rayn @@ 2014/08/21
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 1 << 30;
const int MAXN = 2500;

struct ISAP
{
    struct Edge
    {
        int from, to, cap, flow;
        Edge() {}
        Edge(int from, int to, int cap, int flow):
            from(from), to(to), cap(cap), flow(flow) {}
    };

    int n, m, s, t;
    bool vis[MAXN];
    int cur[MAXN];
    int pre[MAXN];
    int num[MAXN];
    int d[MAXN];
    vector<Edge> edge;
    vector<int> G[MAXN];
    vector<int>::iterator it;

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        for(int i = 0; i <= n; ++i) {
            G[i].clear();
        }
        edge.clear();
    }
    void AddEdge(int from, int to, int cap)
    {
        edge.push_back(Edge(from, to, cap, 0));
        edge.push_back(Edge(to, from, 0, 0));
        m = edge.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool bfs()
    {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = true;
        d[t] = 0;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(it = G[u].begin();it != G[u].end(); ++it)
            {
                int v = edge[*it^1].from;
                int w = edge[*it^1].cap - edge[*it^1].flow;
                if(!vis[v] && w > 0)
                {
                    vis[v] = true;
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }
        return vis[s];
    }
    int Augment()
    {
        int x = t, a = INF;
        while(x != s)
        {
            Edge& e = edge[pre[x]];
            a = min(a, e.cap - e.flow);
            x = edge[pre[x]].from;
        }
        x = t;
        while(x != s)
        {
            edge[pre[x]].flow += a;
            edge[pre[x]^1].flow -= a;
            x = edge[pre[x]].from;
        }
        return a;
    }
    int MaxFlow(int s, int t)
    {
        this->s = s; this->t = t;
        int flow = 0;
        bfs();
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; ++i) {
            num[d[i]]++;
        }
        int u = s;
        memset(cur, 0, sizeof(cur));
        while(d[s] < n)
        {
            if(u == t)
            {
                flow += Augment();
                u = s;
            }
            bool ok = false;
            for(int i = cur[u]; i < (int) G[u].size(); ++i)
            {
                Edge& e = edge[G[u][i]];
                if(e.cap > e.flow && d[u] == d[e.to] + 1)
                {
                    ok = true;
                    pre[e.to] = G[u][i];
                    cur[u] = i;
                    u = e.to;
                    break;
                }
            }
            if(!ok)
            {
                int low = n-1;
                for(it = G[u].begin(); it != G[u].end(); ++it)
                {
                    Edge& e = edge[*it];
                    if(e.cap > e.flow) {
                        low = min(low, d[e.to]);
                    }
                }
                if(--num[d[u]] == 0) break;
                d[u] = low + 1;
                num[d[u]]++;
                cur[u] = 0;
                if(u != s) {
                    u = edge[pre[u]].from;
                }
            }
        }
        return flow;
    }
};

ISAP Network;
int N, M, S, T;
int maze[64][64];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int Test, cases = 0;
    scanf("%d", &Test);
    while(Test--)
    {
        scanf("%d%d", &N, &M);
        memset(maze, 0, sizeof(maze));
        for(int i = 1; i <= N; ++i)
        {
            char str[64];
            scanf("%s", str);
            for(int j = 0; j < M; ++j)
            {
                if(str[j] == '.') {
                    maze[i][j+1] = 1;
                } else if(str[j] == 'E') {
                    maze[i][j+1] = -1;
                }
            }
        }
        S = 0, T = (N+2)*(M+2)+1;
        Network.Init((N+2)*(M+2)+2);
        int All = 0;
        for(int i = 0; i < N+2; ++i)
        {
            for(int j = 0; j < M+2; ++j)
            {
                if((i+j) % 2 == 0) {
                    if(maze[i][j] == 0) {
                        Network.AddEdge(S, i*(M+2)+j+1, INF);
                    } else if(maze[i][j] == 1) {
                        Network.AddEdge(i*(M+2)+j+1, T, INF);
                    }
                } else if((i+j) % 2 == 1) {
                    if(maze[i][j] == 1) {
                        Network.AddEdge(S, i*(M+2)+j+1, INF);
                    } else if(maze[i][j] == 0) {
                        Network.AddEdge(i*(M+2)+j+1, T, INF);
                    }
                }
                for(int k = 0; k < 4; ++k)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(x >= 0 && y >= 0 && x < N+2 && y < M+2)
                    {
                        All++;
                        Network.AddEdge(i*(M+2)+j+1, x*(M+2)+y+1, 1);
                    }
                }
            }
        }
        printf("Case %d: %d\n", ++cases, All/2 - Network.MaxFlow(S, T));
    }
    return 0;
}

/*
** ZOJ 3760 Treasure Hunting£¨ISAP£©
** Created by Rayn @@ 2014/08/26
** 140ms Accepted
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
        //edge.reserve(MAXM);
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
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = true;
        d[t] = 0;
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(it = G[u].begin(); it != G[u].end(); ++it)
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
        int x = t, A = INF;
        while(x != s)
        {
            Edge& e = edge[pre[x]];
            A = min(A, e.cap - e.flow);
            x = edge[pre[x]].from;
        }
        x = t;
        while(x != s)
        {
            edge[pre[x]].flow += A;
            edge[pre[x]^1].flow -= A;
            x = edge[pre[x]].from;
        }
        return A;
    }
    LL MaxFlow(int s, int t)
    {
        this->s = s; this->t = t;
        LL flow = 0;
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
            for(int i = cur[u]; i < (int) G[u].size(); i++)
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
                num[d[u] = low+1]++;
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
int N, P, S, T;
int pos[MAXN];
int val[MAXN];

bool check(int a, int b)
{
    if(((a ^ b) & 1) == 0) return false;
    if(__gcd(a ^ b, P) == 1)
        return true;
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

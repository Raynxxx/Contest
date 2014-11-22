/*
** ZOJ 3642 Just Another Information Sharing Problem
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 1 << 30;
const int MAXN = 500;
const int MAXM = MAXN*MAXN;

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
    int MaxFlow(int s, int t)
    {
        this->s = s;
        this->t = t;
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

int n, m, info;
int A[MAXN], B[MAXN], C[MAXN];
map<int, int> infoHash;
set<int> child[MAXN];
set<int>::const_iterator it;
ISAP Net;

void Init()
{
    info = 0;
    infoHash.clear();
    for(int i = 0; i <= n; ++i) {
        child[i].clear();
    }
}
bool input()
{
    if(scanf("%d", &n) == EOF) return false;
    Init();
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
        for(int j = 1; j <= A[i]; ++j)
        {
            int id;
            scanf("%d", &id);
            if(!infoHash.count(id)) {
                infoHash[id] = ++info;
            }
            child[i].insert(infoHash[id]);
        }
    }
    scanf("%d", &m);
    return true;
}
int Gao()
{
    Net.Init(n+info+2);
    int S = 0, T = n+info+1;
    for(int i = 1; i <= n; ++i)
    {
        Net.AddEdge(S, i, (i == m)? INF : C[i]);
        for(it = child[i].begin(); it != child[i].end(); ++it)
        {
            Net.AddEdge(i, *it+n, 1);
        }
    }
    for(int i = n+1; i <= n+info; ++i)
    {
        Net.AddEdge(i, T, 1);
    }
    return Net.MaxFlow(S, T);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    while(input())
    {
        printf("%d\n", Gao());
    }
    return 0;
}

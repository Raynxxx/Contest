/*
** ZOJ 3691 Flower
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
const int INF = 1 << 30;
const int MAXN = 300;
const int MAXM = MAXN*MAXN;

struct Point
{
    int x, y, z;
    Point() {}
    Point(int x, int y, int z):
        x(x), y(y), z(z) {}

    void read()
    {
        scanf("%d%d%d", &x, &y, &z);
    }

};

int Dist2(const Point& a, const Point& b)
{
    return sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z);
}

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

ISAP Network;
Point point[MAXN];
int n, full;
int f[MAXN], l[MAXN];
int d[MAXN][MAXN];
vector<int> R;

void Init()
{
    full = 0;
    R.clear();
    memset(d, 0, sizeof(d));
}
bool input()
{
    if(scanf("%d", &n) == EOF) return false;
    Init();
    for(int i = 1; i <= n; ++i)
    {
        point[i].read();
        scanf("%d%d", &f[i], &l[i]);
        full += f[i];
    }
    return true;
}
bool Can(int r, int val)
{
    Network.Init(n+n+1);
    int S = 0, T = 1;
    for(int i = 1; i <= n; ++i)
    {
        Network.AddEdge(S, i, f[i]);
        Network.AddEdge(i, i+n, l[i]);
        for(int j = 1; j <= n; ++j)
        {
            if(d[i][j] <= r) {
                Network.AddEdge(i+n, j, INF);
            }
        }
    }
    return Network.MaxFlow(S, T) != full;
}
int Gao()
{
    for(int i = 1; i <= n; ++i)
    {
        for(int j = i+1; j <= n; ++j)
        {
            d[i][j] = d[j][i] = Dist2(point[i], point[j]);
            R.push_back(d[i][j]);
        }
    }
    sort(R.begin(), R.end());
    R.erase(unique(R.begin(), R.end()), R.end());
    int it = lower_bound(R.begin(), R.end(), 0, Can) - R.begin();
    if(it == R.size()) {
        printf("-1\n");
    } else {
        printf("%.7f\n", sqrt((double)R[it]));
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    while(input()) {
        Gao();
    }
    return 0;
}

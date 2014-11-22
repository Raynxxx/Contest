/*
** ZOJ 3756 Miko Miko Suika
** Created by Rayn @@ 2014/08/21
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 0x3F3F3F3F;
const double EPS = 1e-8;
const int MAXN = 810;
const int MAXC = 25;

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y):
        x(x), y(y) {}
    Point operator + (const Point& p) const
    {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point& p) const
    {
        return Point(x - p.x, y - p.y);
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }
};

double Cross(Point A, Point B)
{
    return A.x*B.y - A.y*B.x;
}
double Dot(Point A, Point B)
{
    return A.x*B.x + A.y*B.y;
}
bool SegmentCross(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-b1, a1-b1), d2 = Cross(a2-b2, a1-b2);
    double d3 = Cross(b1-a1, b2-a1), d4 = Cross(b1-a2, b2-a2);
    if(dcmp(d1)*dcmp(d2) < 0 && dcmp(d3)*dcmp(d4) < 0)
        return true;
    if(dcmp(d1) == 0 && dcmp(Dot(a2-b1, a1-b1)) <= 0)
        return true;
    else if(dcmp(d2) == 0 && dcmp(Dot(a2-b2, a1-b2)) <= 0)
        return true;
    else if(dcmp(d3) == 0 && dcmp(Dot(b1-a1, b2-a1)) <= 0)
        return true;
    else if(dcmp(d4) == 0 && dcmp(Dot(b1-a2, b2-a2)) <= 0)
        return true;
    return false;
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
int N, M, S, T, All;
int C[MAXN];
Point Kedama[MAXN][MAXC];
Point item[MAXN];

void Init()
{
    All = 0;
    S = 0, T = N+M+1;
    Network.Init(N+M+2);
}
bool input()
{
    if(scanf("%d%d", &N, &M) == EOF) return false;
    Init();
    for(int i = 1, A; i <= N; ++i) {
        scanf("%d", &A);
        Network.AddEdge(i+M, T, A);
    }
    for(int i = 1, B; i <= M; ++i) {
        scanf("%d", &B);
        Network.AddEdge(S, i, B);
        All += B;
    }
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &C[i]);
        for(int j = 0; j < C[i]; ++j) {
            Kedama[i][j].read();
        }
        Kedama[i][C[i]] = Kedama[i][0];
    }
    for(int i = 1; i <= M; ++i) {
        item[i].read();
    }
    return true;
}
int Gao()
{
    Point ini(0, 0);
    for(int i = 1; i <= M; ++i) {
        for(int j = 1; j <= N; ++j) {
            for(int k = 0; k < C[j]; ++k) {
                if(SegmentCross(ini, item[i], Kedama[j][k], Kedama[j][k+1])) {
                    Network.AddEdge(i, j+M, INF);
                    break;
                }
            }
        }
    }
    return All - Network.MaxFlow(S, T);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(input())
    {
        printf("%d\n", Gao());
    }
    return 0;
}


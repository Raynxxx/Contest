/*
** ZOJ 2318 Get Out!
** Created by Rayn @@ 2014/08/09
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 310;
const double eps = 1e-8;
const double INF = 1e20;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    void read() {
        scanf("%lf%lf", &x, &y);
    }
};

double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Dot(Point a, Point b)
{
    return a.x*b.x + a.y*b.y;
}
double Length(Point a)
{
    return sqrt(Dot(a, a));
}
double Cross(Point a, Point b)
{
    return a.x*b.y - a.y*b.x;
}
double Angle(Point a, Point b)
{
    return acos(Dot(a, b) / Length(a) / Length(b));
}
struct Circle
{
    Point o;
    double r;

    Circle() {}
    Circle(Point o, double r):
        o(o), r(r) {}
    void read() {
        o.read();
        scanf("%lf", &r);
    }
};

struct Graph
{
    struct Edge
    {
        int from, to;
        double w;
        int next;

        Edge() {}
        Edge(int from, int to, double w, int next):
            from(from), to(to), w(w), next(next) {}
    };

    int n, sz;
    bool inq[maxn];
    int cnt[maxn];
    double dis[maxn];
    int head[maxn];
    Edge edge[maxn*maxn];

    void Init(int n)
    {
        this->n = n;
        sz = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to, double w)
    {
        edge[sz] = Edge(from, to, w, head[from]);
        head[from] = sz++;
    }
    bool BellmanFord()
    {
        memset(inq, false, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        fill(dis, dis+n, 0);
        queue<int> Q;
        for(int i = 0; i < n; ++i)
        {
            Q.push(i);
            inq[i] = true;
        }
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for (int i = head[u]; i != -1; i = edge[i].next)
            {
                int v = edge[i].to;
                double w = edge[i].w;
                if(dis[v] > dis[u] + w + eps)
                {
                    dis[v] = dis[u] + w;
                    if(!inq[v])
                    {
                        Q.push(v);
                        inq[v] = true;
                        if(++cnt[v] >= n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
};

Circle island[maxn];
Point kolo;
Graph Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, n;
    double r0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            island[i].read();
        }
        kolo.read();
        scanf("%lf", &r0);
        for(int i = 0; i < n; ++i)
        {
            island[i].o.x -= kolo.x;
            island[i].o.y -= kolo.y;
            island[i].r += r0;
        }
        Solver.Init(n);
        for(int i = 0; i < n; ++i)
        {
            for(int j = i+1; j < n; ++j)
            {
                if(Distance(island[i].o, island[j].o) >= island[i].r + island[j].r - eps)
                    continue;
                bool flag = (Cross(island[i].o, island[j].o) >= 0);
                double ang = Angle(island[i].o, island[j].o);
                Solver.AddEdge(i, j, (flag? ang : -ang));
                Solver.AddEdge(j, i, (flag? -ang : ang));
            }
        }
        printf(Solver.BellmanFord()? "YES\n" : "NO\n");
        if(T > 0)
            puts("");
    }
    return 0;
}

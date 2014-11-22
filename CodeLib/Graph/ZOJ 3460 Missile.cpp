/*
** ZOJ 3460 Missile
** Created by Rayn @@ 2014/08/11
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 52;
const int maxm = maxn*maxn;
const double eps = 1e-10;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
};

double Dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

struct Hungarian
{
    struct Edge
    {
        int from, to;
        int next;
        Edge() {}
        Edge(int from, int to, int next):
            from(from), to(to), next(next) {}
    };

    int nx, sz;
    bool cover[maxm];
    int link[maxm];
    int head[maxn];
    Edge edge[maxm*maxn];

    void Init(int nx)
    {
        this->nx = nx;
        sz = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to)
    {
        edge[sz] = Edge(from, to, head[from]);
        head[from] = sz++;
    }
    bool Find(int u)
    {
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(!cover[v])
            {
                cover[v] = true;
                if(link[v] == -1 || Find(link[v]))
                {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch()
    {
        int cnt = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= nx; ++i)
        {
            memset(cover, false, sizeof(cover));
            if(Find(i))
                cnt++;
        }
        return cnt;
    }
};

int n, m;
double t1, t2, v;
double dis[maxn][maxn];
Point target[maxn], tower[maxn];
Hungarian Solver;

bool Check(double t)
{
    Solver.Init(m);
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            double t0 = 0;
            for(int k = 1; k <= m; k++)
            {
                t0 += t1;
                if(t0 + dis[i][j] <= t) {
                    Solver.AddEdge(i, j*m+k);
                } else {
                    break;
                }
                t0 += t2;
            }
        }
    }
    return Solver.MaxMatch() == m;
}


int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%lf%lf%lf", &n, &m, &t1, &t2, &v) != EOF)
    {
        t1 /= 60;
        for(int i = 1; i <= m; ++i)
        {
            target[i].read();
        }
        for(int i = 1; i <= n; ++i)
        {
            tower[i].read();
        }
        for(int i = 1; i <= m; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                dis[i][j] = Dist(target[i], tower[j]) / v;
            }
        }
        double l = 0, r = 1e4;
        while(l + eps < r)
        {
            double mid = (l + r) / 2;
            if(Check(mid))
                r = mid;
            else
                l = mid;
        }
        printf("%.6f\n", r);
    }
    return 0;
}

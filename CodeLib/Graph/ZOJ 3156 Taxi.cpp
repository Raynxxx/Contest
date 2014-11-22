/*
** ZOJ 3156 Taxi
** Created by Rayn @@ 2014/08/02
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const double EPS = 1e-5;
const int maxn = 105;

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

struct Edge
{
    int from, to;
    int next;
    Edge() {}
    Edge(int from, int to, int next):
        from(from), to(to), next(next) {}
};

struct Hungarian
{
    int n, sz;
    bool vis[maxn];
    int link[maxn];
    int head[maxn];
    Edge edge[maxn*maxn];

    void Init(int n)
    {
        this->n = n;
        sz = 0;
        memset(head, -1, sizeof(head));
        memset(edge, -1, sizeof(edge));
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
            if(!vis[v])
            {
                vis[v] = true;
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
        for(int i = 1; i <= n; ++i)
        {
            memset(vis, false, sizeof(vis));
            if(Find(i))
                cnt++;
        }
        return cnt;
    }
};

Hungarian MatchSolver;
Point peo[maxn], car[maxn];
int n, m;
double v;

double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
void Read()
{
    for(int i = 1; i <= n; ++i) {
        peo[i].read();
    }
    for(int i = 1; i <= m; ++i) {
        car[i].read();
    }
    scanf("%lf", &v);
}
bool Check(double time)
{
    MatchSolver.Init(n);
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            double t = Distance(peo[i], car[j]) / v;
            if(t + EPS <= time)
                MatchSolver.AddEdge(i, j);
        }
    }
    return (MatchSolver.MaxMatch() == n ? true : false);
}
void Work()
{
    double maxt = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            maxt = max(maxt, Distance(peo[i], car[j])/v);
        }
    }
    double left = 0, right = maxt;
    while(left + EPS < right)
    {
        double mid = (left + right) / 2.0;
        if(Check(mid))
            right = mid;
        else
            left = mid;
    }
    printf("%.2f\n", left);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Read();
        Work();
    }
    return 0;
}

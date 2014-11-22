/*
** HDU 4606 Occupy Cities
** Created by Rayn @@ 2014/08/08
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 510;
const int maxm = 30010;
const double DINF = 1e10;
const double eps = 1e-7;

int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    return (x < 0)? -1 : 1;
}
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    inline Point operator + (const Point& p) const
    {
        return Point(x+p.x, y+p.y);
    }
    inline Point operator - (const Point& p) const
    {
        return Point(x-p.x, y-p.y);
    }
    inline bool operator == (const Point& p) const
    {
        return dcmp(x-p.x) == 0 && dcmp(y-p.y) == 0;
    }
    void read()
    {
        scanf("%lf %lf", &x, &y);
    }
};
typedef Point Vector;

struct Line
{
    Point a, b;

    Line() {}
    Line(Point a, Point b): a(a), b(b) {}

    void read()
    {
        a.read();
        b.read();
    }
    inline bool operator == (const Line& p) const
    {
        return (a == p.a && b == p.b) || (a == p.b && b == p.a);
    }
};

double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
double Dist(const Point& a, const Point& b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
bool SegmentCross(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-b1, a1-b1), d2 = Cross(a2-b2, a1-b2);
    double d3 = Cross(b1-a1, b2-a1), d4 = Cross(b1-a2, b2-a2);
    if(dcmp(d1*d2) < 0 && dcmp(d3*d4) < 0)
        return true;
    return false;
}

struct Edge
{
    int from, to;
    int next;

    Edge() {}
    Edge(int from , int to, int next):
        from(from), to(to), next(next) {}
};

int n, m, p, sz;
int occupy[maxn];
bool cover[maxn];
int link[maxn], head[maxn];
double dis[maxn][maxn];
Edge edge[maxm];
Point city[maxn];
Line barrier[maxn];

void Floyd(int n)
{
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(dis[i][k] + dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
            }
        }
    }
}
inline void AddEdge(int from, int to)
{
    edge[sz].from = from;
    edge[sz].to = to;
    edge[sz].next = head[from];
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
    for(int i = 1; i <= n; ++i)
    {
        memset(cover, false, sizeof(cover));
        if(Find(i))
            cnt++;
    }
    return cnt;
}
bool Check(double food)
{
    sz = 0;
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; ++i)
    {
        for(int j = i+1; j <= n; ++j)
        {
            if(dis[occupy[i]][occupy[j]] <= food)
            {
                AddEdge(occupy[i], occupy[j]);
            }
        }
    }
    return n - MaxMatch() <= p;
}
double Fuck()
{
    double l = 0, r = DINF;
    while(l + eps < r)
    {
        double mid = (l + r) / 2.0;
        if(Check(mid))
            r = mid;
        else
            l = mid;
    }
    return r;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &p);
        for(int i = 1; i <= n; ++i)
        {
            city[i].read();
        }
        for(int i = 1; i <= m; ++i)
        {
            barrier[i].read();
            city[n+i*2-1] = barrier[i].a;
            city[n+i*2] = barrier[i].b;
        }
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &occupy[i]);
        }
        for(int i = 1; i <= n+m*2; ++i)
        {
            for(int j = 1; j <= n+m*2; ++j)
            {
                dis[i][j] = (i == j)? 0.0 : DINF;
            }
        }
        for(int i = 1; i <= n+m*2; ++i)
        {
            for(int j = i+1; j <= n+m*2; ++j)
            {
                bool inter = false;
                for(int k = 1; k <= m; ++k)
                {
                    if(barrier[k] == Line(city[i], city[j]))
                        continue;
                    if(SegmentCross(barrier[k].a, barrier[k].b, city[i], city[j]))
                    {
                        inter = true;
                        break;
                    }
                }
                if(!inter)
                    dis[i][j] = dis[j][i] = Dist(city[i], city[j]);
            }
        }
        Floyd(n+m*2);
        double res = Fuck();
        printf("%.2f\n", res);
    }
    return 0;
}

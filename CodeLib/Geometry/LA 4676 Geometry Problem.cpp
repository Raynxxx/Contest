/*
** LA 4676 Geometry Problem
** Created by Rayn @@ 2014/06/11
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 110;
const double INF = 1e18;

struct Point
{
    double x, y;

    Point(double x = 0, double y = 0) :
        x(x), y(y) {}

    Point operator + (const Point& a) {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point& a) {
        return Point(x - a.x, y - a.y);
    }
    Point operator * (double t) {
        return Point(x * t, y * t);
    }
    Point operator / (double t) {
        return Point(x / t, y / t);
    }
    bool operator < (const Point& a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
} tri[5][5], v[5];

typedef Point Vector;

struct Line
{
    Point from, to;
    Line() {}
    Line(Point a, Point b) : from(a), to(b) {}
} street[MAX];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Dot(Vector a, Vector b)
{
    return a.x*b.x + a.y*b.y;
}
double Cross(Vector a, Vector b)
{
    return a.x*b.y - a.y*b.x;
}
double VectorLen(Point x)
{
    return sqrt(Dot(x, x));
}
bool OnSegment(Point p, Point a, Point b)
{
    return dcmp(Dot(a-p, b-p)) <= 0;
}
Point GetInter(Line p, Line q)
{
    Vector u = p.from - q.from;
    Vector v = p.from - p.to, w = q.from - q.to;
    double t = Cross(u, w) / Cross(v, w);
    return p.from + (p.to - p.from) * t;
}
double Solve(int a, int b)
{
    double res = INF;
    Point vec = v[a] - v[b];
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(dcmp(Cross(vec, tri[b][j] - tri[b][j+1])) == 0)
                continue;
            Point inter = GetInter(Line(tri[a][i], tri[a][i] + vec), Line(tri[b][j], tri[b][j+1]));
            if(!OnSegment(inter, tri[b][j], tri[b][j+1]))
                continue;
            Point dir = inter - tri[a][i];
            if(dcmp(Dot(dir, vec)) < 0)
                continue;
            res = min(res, VectorLen(dir) / VectorLen(vec));
        }
    }
    return res;
}

int main()
{
    int t;
    double x1, x2, x3, y1, y2, y3;
    double vx[2], vy[2];

    scanf("%d", &t);
    while(t--)
    {
        for(int i = 0; i < 2; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                scanf("%lf%lf", &tri[i][j].x, &tri[i][j].y);
            }
            tri[i][3] = tri[i][0];
            scanf("%lf%lf", &v[i].x, &v[i].y);
        }
        double ans = min(Solve(0, 1), Solve(1, 0));
        if(ans >= INF)
            printf("NO COLLISION\n");
        else
            printf("%.9f\n", ans+EPS);
    }
    return 0;
}

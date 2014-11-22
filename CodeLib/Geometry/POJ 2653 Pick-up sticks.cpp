/*
** POJ 2653 Pick-up sticks
** Created by Rayn @@ 2014/05/27
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int INF = 0x7FFFFFFF;
const int MAX = 100010;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
};
struct Line {
    int id;
    Point a, b;
    Line() {}
    Line(int id, Point a, Point b) :
        id(id), a(a), b(b) {}
};
typedef Point Vector;

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double OnSeg(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
bool SegIntersect(Line l1, Line l2)
{
    Point a1 = l1.a, a2 = l1.b;
    Point b1 = l2.a, b2 = l2.b;
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1);
    double d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    if (dcmp(d1)*dcmp(d2) < 0 && dcmp(d3)*dcmp(d4) < 0)
        return true;
    else if (d1 == 0 && OnSeg(a1, a2, b1))
        return true;
    else if (d2 == 0 && OnSeg(a1, a2, b2))
        return true;
    else if (d3 == 0 && OnSeg(b1, b2, a1))
        return true;
    else if (d4 == 0 && OnSeg(b1, b2, a2))
        return true;
    else
        return false;
}

Line stick[MAX];
int ans[MAX];

int main()
{
    int n;
    double x1, x2, y1, y2;
    while(scanf("%d", &n) != EOF && n)
    {
        memset(ans, 0, sizeof(ans));
        for(int i = 1; i <= n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            stick[i] = Line(i, Point(x1, y1), Point(x2, y2));
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            int flag = 1;
            for(int j = i+1; j <= n; ++j)
            {
                if (SegIntersect(stick[i], stick[j]))
                {
                    flag = 0;
                    break;
                }
            }
            if(flag)
            {
                ans[cnt++] = stick[i].id;
            }
        }
        printf("Top sticks:");
        for(int i = 0; i < cnt; ++i)
        {
            printf(" %d%c", ans[i], (i == cnt-1)? '.' : ',');
        }
        printf("\n");
    }
    return 0;
}

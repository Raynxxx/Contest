/*
** HDU 4454 Stealing a Cake
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double INF = 1e20;
const double PI = acos(-1.0);

struct Point
{
    double x, y;
    Point(double x=0, double y=0):
        x(x), y(y) {}
};

struct Circle
{
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r):
        c(c), r(r) {}
    Point PointOnCircle(double a)
    {
        return Point(c.x + cos(a)*r, c.y + sin(a)*r);
    }
} circle;

double Dis(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Solve(Point t, Point p1, Point p2)
{
    double cx = t.x, cy = t.y;
    double x1 = min(p1.x, p2.x);
    double x2 = max(p1.x, p2.x);
    double y1 = min(p1.y, p2.y);
    double y2 = max(p1.y, p2.y);
    if(x1 <= cx && cx <= x2)
    {
        return min(fabs(cy-y1), fabs(cy-y2));
    }
    if(y1 <= cy && cy <= y2)
    {
        return min(fabs(cx-x1), fabs(cx-x2));
    }

    double res = Dis(t, Point(x1, y1));
    res = min(res, Dis(t, Point(x1, y2)));
    res = min(res, Dis(t, Point(x2, y1)));
    res = min(res, Dis(t, Point(x2, y2)));
    return res;
}
int main()
{
#ifdef HotWhite
    freopen("in.txt", "r", stdin);
#endif

    double x, y, cx, cy, x1, y1, x2, y2, r;
    Point ant, p1, p2;
    while(scanf("%lf%lf", &x, &y) != EOF)
    {
        if(!x && !y)
            break;
        scanf("%lf%lf%lf", &cx, &cy, &r);
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);

        ant = Point(x, y);
        circle = Circle(Point(cx, cy), r);
        p1 = Point(x1, y1);
        p2 = Point(x2, y2);
        double ans = INF;
        int N = 2000;
        for(int i = 0; i <= N; ++i)
        {
            Point tmp = circle.PointOnCircle(2*PI*i/N);
            ans = min(ans, Dis(ant, tmp) + Solve(tmp, p1, p2));
        }
        printf("%.2f\n", ans);
    }
    return 0;
}

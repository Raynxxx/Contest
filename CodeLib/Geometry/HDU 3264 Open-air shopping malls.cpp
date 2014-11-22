/*
** HDU 3264 Open-air shopping malls
** Created by Rayn @@ 2014/06/10
** 二分半径+枚举圆心+余弦定理求相交
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
typedef long long LL;
const int MAX = 30;
const double PI = acos(-1.0);

struct Point {
   double x, y;
   Point(double x=0.0, double y=0.0) :
       x(x), y(y) {}
};
struct Circle {
    Point mid;
    double r;
    Circle() {}
    Circle(Point m, double r) :
        mid(m), r(r) {}
} mall[MAX];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0) ? -1 : 1;
}
double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Area(Circle a)
{
    return a.r*a.r*PI;
}
double CoverArea(Circle a, Circle b)
{
    double d = Distance(a.mid, b.mid);
    if(dcmp(d-a.r-b.r) >= 0)
        return 0;
    if(dcmp(fabs(a.r-b.r)-d) >= 0)
        return (a.r < b.r)? Area(a) : Area(b);
    double ang1 = acos((a.r*a.r + d*d - b.r*b.r)/(2*a.r*d));
    double ang2 = acos((b.r*b.r + d*d - a.r*a.r)/(2*b.r*d));
    return ang1*a.r*a.r + ang2*b.r*b.r - a.r*d*sin(ang1);
}
bool Solve(double midr, int n)
{
    for(int i = 0, j; i < n; ++i)
    {
        Circle um = mall[i];
        um.r = midr;
        for(j = 0; j < n; ++j)
        {
            if(CoverArea(um, mall[j]) < Area(mall[j])/2)
                break;
        }
        if(j == n)
            return true;
    }
    return false;
}
int main()
{
    int t, n;
    double x, y, r;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf", &x, &y, &r);
            mall[i] = Circle(Point(x, y), r);
        }
        double l = 0, r = 1e6;
        while(dcmp(r-l) > 0)
        {
            double mid = (l + r) / 2;
            if(Solve(mid, n))
                r = mid;
            else
                l = mid;
        }
        printf("%.4f\n", r);
    }
    return 0;
}

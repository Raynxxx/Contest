/*
** CF 8D Two Friends
** Created by Rayn @@ 2014/09/09
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const double EPS = 1e-10;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator + (const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double& p) const {
        return Point(x * p, y * p);
    }
};

double t1, t2;
Point cinema, shop, house;

double sqr(double x)
{
    return x * x;
}
double Dist(Point a, Point b)
{
    return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}
//(st -> mid -> ed) - (st -> ed) <= limit
double Gao(Point st, Point ed, Point mid, double limit)
{
    if(Dist(st, mid) + Dist(mid, ed) <= limit + Dist(st, ed)) {
        return Dist(st, ed) + limit - Dist(mid, ed);
    }
    double l = 0.0, r = 1.0;
    while(l + EPS <= r)
    {
        double m = (l + r) / 2.0;
        Point p = st + (mid - st) * m;
        if(Dist(st, p) + Dist(p, ed) <= limit + Dist(st, ed)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l * Dist(st, mid);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%lf%lf", &t1, &t2) != EOF)
    {
        cinema.read();
        house.read();
        shop.read();
        double res = 0;
        res = max(res, min(Gao(cinema, shop, house, t1), Gao(cinema, house, house, t2)));
        res = max(res, min(Gao(cinema, shop, shop, t1), Gao(cinema, house, shop, t2)));
        if(Dist(cinema, shop) + Dist(shop, house) <= t2 + Dist(cinema, house)) {
            res = max(res, min(Dist(cinema, house) + t2, Dist(cinema, shop) + Dist(shop, house) + t1));
        }
        double l = 0.0, r = 1.0;
        while(l + EPS < r)
        {
            double m1 = l + (r - l) / 3.0;
            double m2 = r - (r - l) / 3.0;
            Point p1 = house + (shop - house) * m1;
            Point p2 = house + (shop - house) * m2;
            double s1 = min(Gao(cinema, shop, p1, t1), Gao(cinema, house, p1, t2));
            double s2 = min(Gao(cinema, shop, p2, t1), Gao(cinema, house, p2, t2));
            if(s1 > s2) {
                r = m2;
                res = max(res, s1);
            } else {
                l = m1;
                res = max(res, s2);
            }
        }
        printf("%.6f\n", res);
    }
    return 0;
}


/*
** HDU 3932 Groundhog Build Home
** Created by Rayn @@ 2014/08/08
** 随机增量法，期望复杂度接近线性O(n).
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;
const int maxn = 1010;

int n;
double W, H, R;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator + (const Point& p) {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) {
        return Point(x-p.x, y-p.y);
    }
    Point operator - (const double& p) {
        return Point(x*p, y*p);
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }
} p[maxn], ini;

typedef Point Vector;

double Dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
//求三点的外接圆圆心
Point CircleCenter(Point a, Point b, Point c)
{
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1*b2 - c2*b1)/d, a.y + (a1*c2 - a2*c1)/d);
}
void MinCoverCircle()
{
    random_shuffle(p, p+n);
    ini = p[0], R = 0;
    for(int i = 1; i < n; ++i)
    {
        if(Dist(ini, p[i]) + EPS > R)
        {
            ini = p[i], R = 0;
            for(int j = 0; j < i; ++j)
            {
                if(Dist(ini, p[j]) + EPS > R)
                {
                    ini.x = (p[i].x + p[j].x) / 2;
                    ini.y = (p[i].y + p[j].y) / 2;
                    R = Dist(ini, p[j]);
                    for(int k = 0; k < j; ++k)
                    {
                        if(Dist(ini, p[k]) + EPS > R)
                        {
                            ini = CircleCenter(p[i], p[j], p[k]);
                            R = Dist(ini, p[k]);
                        }
                    }
                }
            }
        }
    }

}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%lf%lf%d", &W, &H, &n) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            p[i].read();
        }
        MinCoverCircle();
        printf("(%.1f,%.1f).\n", ini.x, ini.y);
        printf("%.1f\n", R);
    }
    return 0;
}

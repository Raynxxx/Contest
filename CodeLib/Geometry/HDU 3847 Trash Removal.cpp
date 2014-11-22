/*
** HDU 3847 Trash Removal
** Created by Rayn @@ 2014/08/08
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 110;
const double DINF = 1e10;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator + (const Point& p) const
    {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) const
    {
        return Point(x-p.x, y-p.y);
    }
    bool operator < (const Point& p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
    void write()
    {
        printf("%.2f %.2f\n", x, y);
    }
};

typedef Point Vector;

double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
double Length(const Vector& A)
{
    return sqrt(A.x*A.x + A.y*A.y);
}
double DistToLine(Point p, Point a, Point b)
{
    Vector v1 = b-a, v2 = p-a;
    return fabs(Cross(v1, v2) / Length(v1));
}
int ConvexHull(Point ch[], Point p[], int n)
{
    sort(p, p+n);

    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; --i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
double Solve(Point ch[], int m)
{
    double ret = DINF;
    for(int i = 0; i < m; i++)
    {
        double d = -DINF;
        for(int j = 0; j < m; ++j)
        {
            d = max(d, DistToLine(ch[j], ch[i], ch[(i+1)%m]));
        }
        ret = min(ret, d);
    }
    return ret;
}

Point p[maxn], ch[maxn];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, cases = 0;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            p[i].read();
        }
        int m = ConvexHull(ch, p, n);
        double res = Solve(ch, m);
        res = ceil(res * 100) / 100.0;
        printf("Case %d: %.2f\n", ++cases, res);
    }
    return 0;
}

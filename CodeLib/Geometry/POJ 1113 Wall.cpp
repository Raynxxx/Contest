/*
** POJ 1113 Wall
** Created by Rayn @@ 2014/06/02
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX = 1005;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    bool operator < (const Point &rhs) const {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    Point operator - (const Point& rhs) const {
        return Point(x-rhs.x, y-rhs.y);
    }
} king[MAX], dot[MAX];

typedef Point Vector;

double Length(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
int Tubao(Point *p, int n)
{
    sort(p, p+n);
    int m = 0;
    for(int i=0; i<n; ++i)
    {
        while(m > 1 && Cross(dot[m-1]-p[i], dot[m-2]-p[i])<=0)
            m--;
        dot[m++] = p[i];
    }
    int k = m;
    for(int i=n-2; i>=0; i--)
    {
        while(m > k && Cross(dot[m-1]-p[i], dot[m-2]-p[i])<=0)
            m--;
        dot[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int n, l;

    scanf("%d%d", &n, &l);
    for(int i = 0; i < n; ++i)
    {
        scanf("%lf %lf", &king[i].x, &king[i].y);
    }
    int cnt = Tubao(king, n);

    double area = 0.0;
    for(int i = 0; i < cnt; ++i)
    {
        area += Length(dot[i], dot[(i+1)%n]);
    }
    area += 2 * PI * l;
    printf("%.f", area);
    return 0;
}

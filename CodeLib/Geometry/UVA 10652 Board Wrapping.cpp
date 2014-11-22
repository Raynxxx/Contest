/*
** UVA 10652 Board Wrapping
** Created by Rayn @@ 2014/06/13
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int MAX = 2500;
const double INF = 1e100;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) :
        x(x), y(y) {}
    Point operator + (const Point& rhs) {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point& rhs) {
        return Point(x - rhs.x, y - rhs.y);
    }
    bool operator < (const Point& rhs) const {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    void Get() {
        scanf("lf%lf", x, y);
    }
    void Print() {
        printf("%.2f %.2f\n", x, y);
    }
} po[MAX], tubao[MAX];
typedef Point Vector;

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Cross(Vector a, Vector b)
{
    return a.x*b.y - a.y*b.x;
}
double ToRad(double x)
{
    return x*PI/180.0;
}
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}
double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}
double PolygonArea(Point *poly, int n)
{
    double ans = 0.0;
    for(int i = 1; i < n-1; ++i)
    {
        ans += Area2(poly[0], poly[i], poly[i+1]);
    }
    return ans/2;
}
int ConvexHull(Point *p, int n, Point *ch)
{
    sort(p, p+n);
    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; --i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
int main()
{
    int t, n;
    double x, y, w, h, theta;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int ct = 0;
        double BoardArea = 0.0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf%lf", &x, &y, &w, &h, &theta);
            Point Center(x, y);
            double rad = -ToRad(theta);
            po[ct++] = Center + Rotate(Vector(-w/2, -h/2), rad);
            po[ct++] = Center + Rotate(Vector(-w/2, h/2), rad);
            po[ct++] = Center + Rotate(Vector(w/2, -h/2), rad);
            po[ct++] = Center + Rotate(Vector(w/2, h/2), rad);
            BoardArea += w*h;
        }
        int tubaoCnt = ConvexHull(po, ct, tubao);
        double total = PolygonArea(tubao, tubaoCnt);
        printf("%.1f %%\n", BoardArea*100/total);
    }
    return 0;
}

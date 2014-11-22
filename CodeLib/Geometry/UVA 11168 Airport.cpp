/*
** UVA 11168 Airport
** Created by Rayn @@ 2014/06/14
** 太傻比了，果然考六级考昏头了
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int MAX = 10010;
const double INF = 1e20;
const double PI = acos(-1.0);

struct Point
{
    double x, y, sum;
    Point(double x=0, double y=0) :
        x(x), y(y), sum(x+y) {}
    Point operator + (const Point& rhs)
    {
        return Point(x+rhs.x, y+rhs.y);
    }
    Point operator - (const Point& rhs)
    {
        return Point(x-rhs.x, y-rhs.y);
    }
    void OutputPoint()
    {
        printf("%lf%lf", x, y);
    }
};
typedef Point Vector;

double sumx, sumy;
Point po[MAX], tubao[MAX];

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
bool cmp(const Point& a, const Point& b)
{
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
int ConvexHull(Point *p, int n, Point *ch)
{
    sort(p, p+n, cmp);
    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
double GetDis(Point a, Point b, int N)
{
    double A = a.y - b.y;
    double B = b.x - a.x;
    double C = a.x*b.y - a.y*b.x;
    return fabs(A*sumx + B*sumy + N*C) / sqrt(A*A + B*B);
}
int main()
{
    int t, n, cases = 0;
    double x, y;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        sumx = sumy = 0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            sumx += x; sumy += y;
            po[i] = Point(x, y);
        }
        int m = ConvexHull(po, n, tubao);
        //printf("%d\n", m); 又傻逼了，居然没有取消注释
        if(m <= 2)
        {
            printf("Case #%d: 0.000\n", ++cases);
            continue;
        }
        double ans = INF;
        for(int i = 0; i < m; ++i)
        {
            double dis = GetDis(tubao[i], tubao[(i+1)%m], n);
            ans = min(ans, dis);
        }
        printf("Case #%d: %.3f\n", ++cases, ans/n);
    }
    return 0;
}

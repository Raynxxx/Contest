/*
** UVA 10256 The Great Divide
** Created by Rayn @@ 2014/06/17
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const double EPS = 1e-10;
const int MAX = 550;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    bool operator < (const Point& rhs) const
    {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    bool operator == (const Point& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
    Point operator + (const Point& rhs)
    {
        return Point(x+rhs.x, y+rhs.y);
    }
    Point operator - (const Point& rhs)
    {
        return Point(x-rhs.x, y-rhs.y);
    }
    void getPointInput()
    {
        scanf("%lf%lf", &x, &y);
    }
    void PointOutput()
    {
        printf("%.2f %.2f\n", x, y);
    }
};
typedef Point Vector;

Point man1[MAX], man2[MAX];
Point tubao1[MAX], tubao2[MAX];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x > 0)? 1:-1;
}
double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
bool SegProperIntersect(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1),
           d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    return dcmp(d1*d2) < 0 && dcmp(d3*d4) < 0;
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
int IsPointInPolygon(Point p, Point *poly, int n)
{
    int wn = 0;
    for(int i = 0; i < n; i++)
    {
        Point p1 = poly[i];
        Point p2 = poly[(i+1)%n];
        if(p1 == p || p2 == p || OnSegment(p, p1, p2))
            return -1; // 在边界上
        int k = dcmp(Cross(p2-p1, p-p1));
        int d1 = dcmp(p1.y - p.y);
        int d2 = dcmp(p2.y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if (wn != 0)
        return 1; // 内部
    return 0; // 外部
}
bool ConvexPolyDisjoint(Point *ch1, int n1, Point *ch2, int n2)
{
    for(int i = 0; i < n1; i++)
    {
        if(IsPointInPolygon(ch1[i], ch2, n2) != 0)
            return false;
    }
    for(int i = 0; i < n2; i++)
    {
        if(IsPointInPolygon(ch2[i], ch1, n1) != 0)
            return false;
    }
    for(int i = 0; i < n1; ++i)
    {
        for(int j = 0; j < n2; ++j)
        {
            if(SegProperIntersect(ch1[i], ch1[(i+1)%n1], ch2[j], ch2[(j+1)%n2]))
                return false;
        }
    }
    return true;
}
int main()
{
    int m, c;
    while(scanf("%d%d", &m, &c) != EOF)
    {
        if(!m && !c)
            break;

        for(int i = 0; i < m; ++i)
        {
            man1[i].getPointInput();
        }
        for(int i = 0; i < c; ++i)
        {
            man2[i].getPointInput();
        }
        int c1 = ConvexHull(man1, m, tubao1);
        int c2 = ConvexHull(man2, c, tubao2);
        if(ConvexPolyDisjoint(tubao1, c1, tubao2, c2))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

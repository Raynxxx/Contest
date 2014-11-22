/*
** POJ 1410 Intersection
** Created by Rayn @@ 2014/05/30
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
} rect[5], Start, End;

typedef Point Vector;

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
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
    //这道题有端点重合的非规范线段相交，Dot值等于0时即有端点重合
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) <= 0;
}
bool SegIntersect(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1),
        d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    if(dcmp(d1*d2) < 0 && dcmp(d3*d4) < 0)
        return true;
    else if(dcmp(d1) == 0 && OnSegment(b1, a1, a2))
        return true;
    else if(dcmp(d2) == 0 && OnSegment(b2, a1, a2))
        return true;
    else if(dcmp(d3) == 0 && OnSegment(a1, b1, b2))
        return true;
    else if(dcmp(d4) == 0 && OnSegment(a2, b1, b2))
        return true;
    else
        return false;
}
int IsPointInPoly(Point p, Point *poly, int n)
{
    int wn = 0;
    for(int i = 0; i < n; ++i)
    {
        if(OnSegment(p, poly[i], poly[(i+1)%n]))
            return 1;
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if(wn != 0)
        return 1;
    return 0;
}

int HasIntersect(Point *poly, Point a, Point b)
{
    for(int i = 0; i < 4; i++)
    {
        if(SegIntersect(a, b, poly[i], poly[(i+1)%4]))
            return 1;
    }
    return 0;
}
int main()
{
    int n;
    double x1, y1, x2, y2;
    double x3, y3, x4, y4;

    scanf("%d", &n);
    while(n--)
    {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        Start = Point(x1, y1);
        End = Point(x2, y2);
        scanf("%lf%lf%lf%lf", &x3, &y3, &x4, &y4);
        x1 = min(x3, x4); y1 = max(y3, y4);
        x2 = max(x3, x4); y2 = min(y3, y4);
        rect[0] = Point(x1, y2);
        rect[1] = Point(x1, y1);
        rect[2] = Point(x2, y1);
        rect[3] = Point(x2, y2);

        if(HasIntersect(rect, Start, End) || (IsPointInPoly(Start, rect, 4) && IsPointInPoly(End, rect, 4)))
        {
            printf("T\n");
        }
        else
        {
            printf("F\n");
        }
    }
    return 0;
}

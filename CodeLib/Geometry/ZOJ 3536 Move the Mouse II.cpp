/*
** ZOJ 3536 Move the Mouse II
** Created by Rayn @@ 2014/06/15
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const double INF = 1e20;

struct Point
{
    double x, y;
    int state;
    Point(double x=0, double y=0, int s=0) :
        x(x), y(y), state(s) {}
    Point operator - (const Point& rhs) {
        return Point(x-rhs.x, y-rhs.y);
    }
    void GetInput() {
        scanf("%lf%lf%d", &x, &y, &state);
    }
} p1, p2;
typedef Point Vector;

struct Segment
{
    Point a, b;
    Segment() {}
    Segment(Point a, Point b) :
        a(a), b(b) {}
};
double W, H, a, b, r;

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x > 0)? 1 : -1;
}
bool IsInside(Point p1, Point p2)
{
    if(p1.state == 1)
    {
        if(p1.x+a/2 > W || p1.x-a/2 < 0 || p1.y+b/2 > H || p1.y-b/2 < 0)
            return false;
    }
    else if(p1.state == 2)
    {
        if(p1.x+b/2 > W || p1.x-b/2 < 0 || p1.y+a/2 > H || p1.y-a/2 < 0)
            return false;
    }
    if(p2.state == 1)
    {
        if(p2.x+a/2 > W || p2.x-a/2 < 0 || p2.y+b/2 > H || p2.y-b/2 < 0)
            return false;
    }
    else if(p2.state == 2)
    {
        if(p2.x+b/2 > W || p2.x-b/2 < 0 || p2.y+a/2 > H || p2.y-a/2 < 0)
            return false;
    }
    return true;
}
double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double Dis(Point A, Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
bool SegIntersect(Segment s1, Segment s2)
{
    Point a1 = s1.a, a2 = s1.b;
    Point b1 = s2.a, b2 = s2.b;
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1);
    double d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    if(dcmp(d1*d2) < 0 && dcmp(d3*d4) < 0)
        return true;
    else if(dcmp(d1) == 0 && dcmp(Dot(a1-b1, a2-b1)) <= 0)
        return true;
    else if(dcmp(d2) == 0 && dcmp(Dot(a1-b2, a2-b2)) <= 0)
        return true;
    else if(dcmp(d3) == 0 && dcmp(Dot(b1-a1, b2-a1)) <= 0)
        return true;
    else if(dcmp(d4) == 0 && dcmp(Dot(b1-a2, b2-a2)) <= 0)
        return true;
    return false;
}
double Solve1(double l, double r, double ty)
{
    double left = l, right = r, d1, d2;
    while(left+EPS < right)
    {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        d1 = Dis(p1, Point(mid1, ty)) + Dis(Point(mid1, ty), p2);
        d2 = Dis(p1, Point(mid2, ty)) + Dis(Point(mid2, ty), p2);
        if(d1 < d2)
            right = mid2;
        else
            left = mid1;
    }
    return Dis(p1, Point(left, ty)) + Dis(Point(left, ty), p2);
}
double Solve2(double l, double r, double tx)
{
    double left = l, right = r, d1, d2;
    while(left+EPS < right)
    {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        d1 = Dis(p1, Point(tx, mid1)) + Dis(Point(tx, mid1), p2);
        d2 = Dis(p1, Point(tx, mid2)) + Dis(Point(tx, mid2), p2);
        if(d1 < d2)
            right = mid2;
        else
            left = mid1;
    }
    return Dis(p1, Point(tx, left)) + Dis(Point(tx, left), p2);
}
int main()
{
    while(scanf("%lf%lf%lf%lf", &W, &H, &a, &b) != EOF)
    {
        p1.GetInput();
        p2.GetInput();
        r = sqrt(a*a + b*b) / 2;

        if(!IsInside(p1, p2))
        {
            printf("-1\n");
            continue;
        }
        else if(p1.state == p2.state)
        {
            printf("%.3f\n", Dis(p1, p2));
            continue;
        }
        else if(W < 2*r || H < 2*r)
        {
            printf("-1\n");
            continue;
        }

        double x1 = r, y1 = r, x2 = W-r, y2 = H-r;
        double leftx, rightx, upy, downy, ans;
        leftx = min(p1.x, p2.x);
        rightx = max(p1.x, p2.x);
        downy = min(p1.y, p2.y);
        upy = max(p1.y, p2.y);

        Segment s1, s2, s3, s4, mouse;
        s1 = Segment(Point(x1, y1), Point(x2, y1));
        s2 = Segment(Point(x2, y1), Point(x2, y2));
        s3 = Segment(Point(x2, y2), Point(x1, y2));
        s4 = Segment(Point(x1, y2), Point(x1, y1));
        mouse = Segment(p1, p2);

        //与中心矩形相交或者就在其中，直接求向量距离
        if(SegIntersect(s1, mouse) || SegIntersect(s2, mouse) || SegIntersect(s3, mouse) ||
           SegIntersect(s4, mouse) || (p1.x > x1 && p1.x < x2 && p1.y > y1 && p1.y < y2) ||
           (p2.x > x1 && p2.x < x2 && p2.y > y1 && p2.y < y2))
        {
            ans = Dis(p1, p2);
        }
        //在四角的小方格的情况
        else if(leftx > x2 && downy > y2)
        {
            ans = Dis(p1, Point(x2, y2)) + Dis(Point(x2, y2), p2);
        }
        else if(leftx > x2 && upy < y1)
        {
            ans = Dis(p1, Point(x2, y1)) + Dis(Point(x2, y1), p2);
        }
        else if(rightx < x1 && upy < y1)
        {
            ans = Dis(p1, Point(x1, y1)) + Dis(Point(x1, y1), p2);
        }
        else if(rightx < x1 && downy > y2)
        {
            ans = Dis(p1, Point(x1, y2)) + Dis(Point(x1, y2), p2);
        }
        else    //在四个边上的矩形中的情况
        {
            ans = INF;
            ans = min(ans, Solve1(x1, x2, y1));
            ans = min(ans, Solve1(x1, x2, y2));
            ans = min(ans, Solve2(y1, y2, x1));
            ans = min(ans, Solve2(y1, y2, x2));
        }
        printf("%.3f\n", ans);
    }
    return 0;
}


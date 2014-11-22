/*
** ZOJ 3534 Move the Mouse I
** Created by Rayn @@ 2014/06/15
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;

struct Point
{
    double x, y;
    int state;
    Point(double x=0, double y=0, int s=0) :
        x(x), y(y), state(s) {}
    void GetInput() {
        scanf("%lf%lf%d", &x, &y, &state);
    }
} p1, p2;

double W, H, a, b, r;

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
//两点之间的曼哈顿距离ManhattanDis
double Dis(Point a, Point b)
{
    return fabs(a.x-b.x) + fabs(a.y-b.y);
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
        if(p1.state == p2.state)
        {
            printf("%.3f\n", Dis(p1, p2));
            continue;
        }
        double x1 = r, y1 = r;
        double x2 = W - r, y2 = H - r;

        if(W < 2*r || H < 2*r)
        {
            printf("-1\n");
            continue;
        }
        double leftx, rightx, upy, downy, ans;
        leftx = min(p1.x, p2.x);
        rightx = max(p1.x, p2.x);
        downy = min(p1.y, p2.y);
        upy = max(p1.y, p2.y);

        //直接分成9个部分考虑很直观
        if(leftx > x2 && downy > y2)
        {
            ans = Dis(p1, Point(x2, y2)) + Dis(Point(x2, y2), p2);
        }
        else if(leftx > x2 && upy < y1)
        {
            ans = Dis(p1, Point(x2, y1)) + Dis(Point(x2, y1), p2);
        }
        else if(rightx < x1 && upy < y1)   //手贱写顺(错)了ORZ
        {
            ans = Dis(p1, Point(x1, y1)) + Dis(Point(x1, y1), p2);
        }
        else if(rightx < x1 && downy > y2)
        {
            ans = Dis(p1, Point(x1, y2)) + Dis(Point(x1, y2), p2);
        }
        else if(leftx > x2)
        {
            ans = Dis(p1, Point(x2, p1.y)) + Dis(Point(x2, p1.y), p2);
        }
        else if(rightx < x1)
        {
            ans = Dis(p1, Point(x1, p1.y)) + Dis(Point(x1, p1.y), p2);
        }
        else if(downy > y2)
        {
            ans = Dis(p1, Point(p1.x, y2)) + Dis(Point(p1.x, y2), p2);
        }
        else if(upy < y1)
        {
            ans = Dis(p1, Point(p1.x, y1)) + Dis(Point(p1.x, y1), p2);
        }
        else
        {
            ans = Dis(p1, p2);
        }
        printf("%.3f\n", ans);
    }
    return 0;
}


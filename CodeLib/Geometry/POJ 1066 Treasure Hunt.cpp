/*
** POJ 1066 Treasure Hunt
** Created by Rayn @@ 2014/05/28
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int INF = 0x7FFFFFFF;
const int MAX = 120;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
};
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
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
bool SegIntersect(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1),
        d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    if (dcmp(d1)*dcmp(d2) < 0 && dcmp(d3)*dcmp(d4) < 0)
        return true;
    else if (d1 == 0 && OnSegment(a1, a2, b1))
        return true;
    else if (d2 == 0 && OnSegment(a1, a2, b2))
        return true;
    else if (d3 == 0 && OnSegment(b1, b2, a1))
        return true;
    else if (d4 == 0 && OnSegment(b1, b2, a2))
        return true;
    else
        return false;
}

Point dot[MAX], trea;

int main()
{
    int n;
    double x1, x2, y1, y2;
    scanf("%d", &n);
    if(n == 0)
    {
        printf("Number of doors = 1\n");
        return 0;
    }
    int cnt = 0;
    for(int i = 0; i < 2*n; i+=2)
    {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        dot[i] = Point(x1, y1);
        dot[i+1] = Point(x2, y2);
    }
    scanf("%lf%lf", &trea.x, &trea.y);

    int ans = INF;
    for(int i = 0; i < 2*n; i++)
    {
        int tmp = 0;
        for(int j = 0; j < 2*n; j+=2)
        {
            if(i == j || i == j+1)
                continue;
            if(SegIntersect(dot[i], trea, dot[j], dot[j+1]))
                tmp++;
        }
        if(tmp < ans)
            ans = tmp;
    }
    printf("Number of doors = %d\n", ans+1);
    return 0;
}

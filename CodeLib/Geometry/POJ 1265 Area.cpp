/*
** POJ 1265 Area
** Created by Rayn @@ 2014/06/10

** 【题目大意】
** 给一个平面上的简单多边形，求边上的点，多边
** 形内的点，多边形面积。

** 【解题思路】
** 1、以格子点为顶点的线段，覆盖的点的个数
** 为GCD(dx,dy)，其中dx dy分别为线段横向占
** 的点数和纵向占的点数。如果dx或dy为0，则
** 覆盖的点数为dy或dx。

** 2、Pick公式：平面上以格子点为顶点的简单
** 多边形的面积=边上的点数/2+内部的点数-1.

** 3、任意一个多边形的面积等于按顺序求相邻
** 两个点与原点组成的向量的叉积之和。
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
typedef long long LL;
const int MAX = 110;
char str[MAX];

struct Point {
    int x, y;
    Point(int x=0, int y=0) :
        x(x), y(y) {}
} po[MAX];
typedef Point Vector;

Vector operator - (const Point& a, const Point& b) {
    return Point(a.x-b.x, a.y-b.y);
}
int IntAbs(int x)
{
    return (x > 0)? x : -x;
}
int gcd(int m, int n)
{
    return (n == 0)? m : gcd(n, m%n);
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}
int main()
{
    int t, m, dx, dy;
    int cases = 0, first = 1;

    scanf("%d", &t);
    while(t--)
    {
        if(!first)
            printf("\n");
        first = 0;
        scanf("%d", &m);
        Point now(0, 0);
        po[0] = now;

        int EdgeP = 0;
        double Area = 0.0;
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &dx, &dy);
            now.x += dx;
            now.y += dy;
            po[i] = now;
            EdgeP += gcd(IntAbs(dx), IntAbs(dy));
            Area += Area2(po[0], po[i], po[i-1]);
        }
        Area = fabs(Area) / 2;
        int InsideP = Area - EdgeP / 2 + 1;

        printf("Scenario #%d:\n", ++cases);
        printf("%d %d %.1f\n", InsideP, EdgeP, Area);
    }
    return 0;
}

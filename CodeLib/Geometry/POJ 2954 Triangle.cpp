/*
** POJ 2954 Triangle
** Created by Rayn @@ 2014/06/10
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
typedef long long LL;
const int MAX = 110;

struct Point {
   int x, y;
   Point(int x=0, int y=0) :
       x(x), y(y) {}
} po[4];
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
int Solve(Point a, Point b)
{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return gcd(IntAbs(dx), IntAbs(dy));
}
int main()
{
    int x1, y1, x2, y2, x3, y3;
    while(scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3) != EOF)
    {
        if(x1==0 && y1==0 && x2==0 && y2==0 && x3==0 && y3==0)
            break;

        po[1] = Point(x1, y1);
        po[2] = Point(x2, y2);
        po[3] = Point(x3, y3);
        int p = Solve(po[1], po[2]) + Solve(po[2], po[3]) + Solve(po[3], po[1]);
        double area = fabs(Area2(po[1], po[2], po[3])) / 2;
        printf("%d\n", (int)(area - p/2 + 1));
    }
    return 0;
}

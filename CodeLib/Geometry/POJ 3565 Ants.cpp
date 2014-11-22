/*
** POJ 3565 Ants
** Created by Rayn @@ 2014/07/23
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 110;
const double EPS = 1e-8;

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void Read()
    {
        scanf("%lf%lf", &x, &y);
    }
} ants[MAXN], apple[MAXN];

typedef Point Vector;

Vector operator + (const Point& A, const Point& B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Point& A, const Point& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
bool SegmentProperIntersect(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1),
        d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    return dcmp(d1*d2) < 0 && dcmp(d3*d4) < 0;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n;
    int link[MAXN];

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 1; i <= n; ++i)
        {
            ants[i].Read();
        }
        for(int i = 1; i <= n; ++i)
        {
            apple[i].Read();
        }
        for(int i = 1; i <= n; ++i)
        {
            link[i] = i;
        }
        while(1)
        {
            bool ok = true;
            for(int i = 1; i <= n; ++i)
            {
                for(int j = 1; j <= n; ++j)
                {
                    if(i == j)
                        continue;
                    if(SegmentProperIntersect(ants[i], apple[link[i]], ants[j], apple[link[j]]))
                    {
                        swap(link[i], link[j]);
                        ok = false;
                    }
                }
            }
            if(ok)
                break;
        }
        for(int i = 1; i <= n; ++i)
        {
            printf("%d\n", link[i]);
        }
    }
    return 0;
}

/*
** LA 6473 Contraband
** Created by Rayn @@ 2014/08/04
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const double PI = acos(-1.0);
const double EPS = 1e-3;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
} P[3], V[3];

double CL[3], a[3];
double dx[] = {0.0, 0.0, EPS, -EPS};
double dy[] = {EPS, -EPS, 0.0, 0.0};

double Cross(Point A, Point B)
{
    return A.x*B.y - A.y*B.x;
}
double Cal(double x, double y)
{
    double ans = 0;
    for(int i = 0; i < 3; i++)
    {
        double tx = x - P[i].x;
        double ty = y - P[i].y;
        double d = Cross(Point(tx, ty), V[i]);
        ans += (CL[i] + 0.2) * d * d;
    }
    return ans;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    P[0] = Point(0.000, 0.000);
    P[1] = Point(3.715, 1.761);
    P[2] = Point(2.894, -2.115);
    int T, cases;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &cases);
        for(int i = 0; i < 3; i++)
        {
            scanf("%lf%lf", &a[i], &CL[i]);
        }
        for(int i = 0; i < 3; i++)
        {
            a[i] = 90 - a[i];
            V[i].x = cos(a[i] * PI/ 180);
            V[i].y = sin(a[i] * PI/ 180);
        }
        double x = P[2].x, y = P[2].y;

        bool ok = true;
        while(ok)
        {
            ok = false;
            double tmp = Cal(x, y);
            for(int i = 0; i < 4; i++)
            {
                double tx = x + dx[i];
                double ty = y + dy[i];
                if(Cal(tx, ty) < tmp)
                {
                    x = tx;
                    y = ty;
                    ok = true;
                    break;
                }
            }
        }
        printf("%d %.3f %.3f\n", cases, x, y);
    }
    return 0;
}

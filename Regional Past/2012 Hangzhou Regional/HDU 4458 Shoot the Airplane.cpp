/*
** HDU 4458 Shoot the Airplane
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 110;
const double EPS = 1e-8;
const double INF = 1e18;

struct Point
{
    double x, y;
    Point(double x=0, double y=0):
        x(x), y(y) {}
} point[MAXN];
typedef Point Vector;

Vector operator + (const Point& A, const Vector& B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Point& A, const Vector& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
Vector operator * (const Point& A, const double& p)
{
    return Vector(A.x*p, A.y*p);
}
Vector operator / (const Point& A, const double& p)
{
    return Vector(A.x/p, A.y/p);
}
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
double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}

double v, b, g;

bool OnSegment(Point p, Point p1, Point p2)
{
    return dcmp(Cross(p1-p, p2-p)) == 0 && dcmp(Dot(p1-p, p2-p)) <= 0;
}
int IsPointInPolygon(Point p, int n)
{
    int wn = 0;
    for(int i = 0; i < n; ++i)
    {
        if(OnSegment(p, point[i], point[(i+1)%n]))
            return 0;
        int k = dcmp(Cross(point[(i+1)%n]-point[i], p-point[i]));
        int d1 = dcmp(point[i].y - p.y);
        int d2 = dcmp(point[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if(wn != 0)
        return 1;
    return 0;
}
int main()
{
#ifdef HotWhite
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%lf%lf%lf", &v, &b, &g) != EOF)
    {
        if(v == 0 && b == 0 && g == 0)
            break;
        scanf("%d", &n);
        double Maxy = -INF;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &point[i].x, &point[i].y);
            Maxy = max(Maxy, point[i].y);
        }
        bool flag = false;
        for(int i = 0; ; ++i)
        {
            double t = (double)i * 0.001;
            Point tmp;
            tmp.x = -v*t;
            tmp.y = b*t - 0.5*g*t*t;
            if(IsPointInPolygon(tmp, n))
            {
                flag = true;
                printf("%.2f\n", t-EPS);
                break;
            }
            if(g == 0 && tmp.y > Maxy)
                break;
            if(tmp.y < 0)
                break;
        }
        if(!flag)
            printf("Miss!\n");
    }
    return 0;
}

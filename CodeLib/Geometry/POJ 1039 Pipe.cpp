/*
** POJ 1039 Pipe
** Created by Rayn @@ 2014/05/30
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 25;
const int INF = 0x7FFFFFFF;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
};
typedef Point Vector;
Point upper[MAX], bottom[MAX];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
bool Check1(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a1-b1, a2-b1), d2 = Cross(a1-b2, a2-b2);
    if(dcmp(d1*d2) <= 0)
        return true;
    return false;
}
bool Check2(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a1-b1, a2-b1), d2 = Cross(a1-b2, a2-b2);
    if(dcmp(d1*d2) < 0)
        return true;
    return false;
}
double GetX(Point a1, Point a2, Point b1, Point b2)
{
    double k1 = (a2.y - a1.y) / (a2.x - a1.x);
    double k2 = (b2.y - b1.y) / (b2.x - b1.x);
    double c1 = a1.y - k1*a1.x;
    double c2 = b1.y - k2*b1.x;
    return (c2 - c1) / (k1 - k2);
}
int main()
{
    int n;
    double x, y;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            upper[i] = Point(x, y);
            bottom[i] = Point(x, y-1);
        }
        int through = 0;
        double ans = -1*INF, tmp;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(Check1(upper[i], bottom[j], upper[0], bottom[0]))
                {
                    int k;
                    for(k = 1; k < n; ++k)
                    {
                        if(!Check1(upper[i], bottom[j], upper[k], bottom[k]))
                        {
                            if(Check2(upper[i], bottom[j], upper[k-1], upper[k]))
                            {
                                tmp = GetX(upper[i], bottom[j], upper[k-1], upper[k]);
                                ans = max(ans, tmp);
                                break;
                            }
                            if(Check2(upper[i], bottom[j], bottom[k-1], bottom[k]))
                            {
                                tmp = GetX(upper[i], bottom[j], bottom[k-1], bottom[k]);
                                ans = max(ans, tmp);
                                break;
                            }
                            ans = max(ans, upper[k-1].x);
                            break;
                        }
                    }
                    if(k == n)
                    {
                        through = 1;
                        i = j = n;
                    }
                }
            }
        }
        if(through)
            printf("Through all the pipe.\n");
        else
            printf("%.2f\n", ans);
    }
    return 0;
}

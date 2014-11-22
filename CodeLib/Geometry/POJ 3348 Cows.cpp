/*
** POJ 3348 Cows
** Created by Rayn @@ 2014/06/09
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 10010;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    bool operator < (const Point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
} po[MAX], tubao[MAX];
typedef Point Vector;

double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Area(Point A, Point B, Point C)
{
    return Cross(B-A, C-A) / 2;
}
int ConvexHull(Point *p, int n, Point *ch)
{
    sort(p, p+n);
    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; --i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
int main()
{
    int n;

    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%lf%lf", &po[i].x, &po[i].y);
    }
    int cnt = ConvexHull(po, n, tubao);
    double ans = 0;
    for(int i = 1; i < cnt-1; ++i)
    {
        ans += Area(tubao[0], tubao[i], tubao[i+1]);
    }
    ans /= 50;
    printf("%.f\n", floor(ans));
    return 0;
}

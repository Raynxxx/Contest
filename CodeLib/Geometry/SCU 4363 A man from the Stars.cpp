/*
** SCU 4363 A man from the Stars
** Created by Rayn @@ 2014/05/30
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 510;

struct Point {
    double x, y;
    Point(double x=0, double y=0) :
        x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
    bool operator < (const Point& a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
};
typedef Point Vector;

struct Line {
    Vector v;
    Point a, b;
    Line() {}
    Line(Point a, Point b) :
        a(a), b(b), v(b-a) {}
    bool operator < (const Line& l) const {
        return v < l.v;
    }
};

Point star[MAX];
Line seg[MAX*MAX];

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
bool OnSegment(Line l1, Line l2)
{
    return dcmp(Cross(l1.b-l1.a, l2.a-l1.a)) == 0;
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
            star[i] = Point(x, y);
        }
        sort(star, star+n);
        int cnt = 0, ans = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = i+1; j < n; ++j)
            {
                seg[cnt++] = Line(star[i], star[j]);
            }
        }
        sort(seg, seg+cnt);
        for(int i = 0, j = 0; i < cnt; i = j)
        {
            while(seg[i].v.x == seg[j].v.x && seg[i].v.y == seg[j].v.y)
                j++;
            for(int k = i; k < j; ++k)
            {
                for(int t = k+1; t < j; ++t)
                {
                    if(!OnSegment(seg[k], seg[t]))
                        ans++;
                }
            }
        }
        printf("%d\n", ans/2);
    }
    return 0;
}

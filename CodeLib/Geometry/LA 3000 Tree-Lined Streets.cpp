/*
** LA 3000 Tree-Lined Streets
** Created by Rayn @@ 2014/06/11
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int MAX = 110;

struct Point
{
    double x, y;
    Point(double x=0, double y=0) : x(x), y(y) {}
    Point operator + (const Point& a) {
        return Point(x+a.x, y+a.y);
    }
    Point operator - (const Point& a) {
        return Point(x-a.x, y-a.y);
    }
    bool operator < (const Point& a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
};
typedef Point Vector;
Point operator * (const Point& a, double t) {
        return Point(a.x*t, a.y*t);
}
struct Line
{
    Point from, to;
    Line() {}
    Line(Point a, Point b) : from(a), to(b) {}
} street[MAX];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Dot(Vector a, Vector b)
{
    return a.x*b.x + a.y*b.y;
}
double Distance(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double Cross(Vector a, Vector b)
{
    return a.x*b.y - a.y*b.x;
}
bool OnSegment(Point p, Point a, Point b)
{
    return dcmp(Cross(a-p, b-p)) == 0 && dcmp(Dot(a-p, b-p)) <= 0;
}
Point GetInter(Line p, Line q)
{
    Vector u = p.from - q.from;
    Vector v = p.to - p.from, w = q.to - q.from;
    double t = Cross(w, u) / Cross(v, w);
    return p.from + (p.to - p.from) * t;
}
double dis[MAX];

int main()
{
    int n, cases = 0;
    double x1, y1, x2, y2;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            street[i] = Line(Point(x1, y1), Point(x2, y2));
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            int dsize = 0;
            double lena = Distance(street[i].from, street[i].to);
            double l1, l2;
            dis[dsize++] = -25.0;
            dis[dsize++] = lena + 25.0;

            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                    continue;
                double lenb = Distance(street[j].from, street[j].to);

                Point inter = GetInter(street[i], street[j]);

                ///*
                l1 = Distance(street[j].from, inter);
                l2 = Distance(street[j].to, inter);
                if(dcmp(lenb-l1-l2) != 0)
                    continue;

                l1 = Distance(street[i].from, inter);
                l2 = Distance(street[i].to, inter);
                if(dcmp(lena-l1-l2) != 0)
                    continue;

                dis[dsize++] = l1;
                /*/
                if(!OnSegment(inter, street[i].from, street[i].to)
                   && !OnSegment(inter, street[j].from, street[j].to))
                    continue;

                dis[dsize++] = Distance(street[i].from, inter);
                */
            }
            sort(dis, dis+dsize);
            for(int j = 0; j+1 < dsize; ++j)
            {
                //printf("%.2f\n", dis[j]);
                ans += (int)((dis[j+1] - dis[j]) / 50.0 + EPS);
            }
            //printf("\n");
        }
        printf("Map %d\n", ++cases);
        printf("Trees = %d\n", ans);
    }
    return 0;
}

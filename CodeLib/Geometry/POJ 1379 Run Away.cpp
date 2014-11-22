/*
** POJ 1379 Run Away
** Created by Rayn @@ 2014/08/06
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 1005;
const double eps = 1e-8;
const double INF = 1e20;
const double PI = acos(-1.0);

int n;
double W, H;
double best[50];

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    bool InRange() {
        if(x+eps > 0 && y+eps > 0 && x-eps < W && y-eps < H)
            return true;
        return false;
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }
} p[maxn], tp[50];

double Dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double getVal(Point ini)
{
    double ret = INF;
    for(int i = 0; i < n; ++i) {
        ret = min(ret, Dist(ini, p[i]));
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lf%lf%d", &W, &H, &n);
        for(int i = 0; i < n; ++i) {
            p[i].read();
        }
        for(int i = 0; i < 15; ++i) {
            tp[i].x = (rand()%1000+1)/1000.0 * W;
            tp[i].y = (rand()%1000+1)/1000.0 * H;
            best[i] = getVal(tp[i]);
        }
        double step = max(W, H) / sqrt(n);
        while(step > 1e-3)
        {
            for(int i = 0; i < 15; ++i)
            {
                Point pre = tp[i], cur;
                for(int j = 0; j < 30; ++j)
                {
                    double ang = (rand()%1000+1)/1000.0 * 2 * PI;
                    cur.x = pre.x + cos(ang) * step;
                    cur.y = pre.y + sin(ang) * step;
                    if(!cur.InRange())
                        continue;
                    double d = getVal(cur);
                    if(d > best[i])
                    {
                        tp[i] = cur;
                        best[i] = d;
                    }
                }
            }
            step *= 0.8;
        }
        int idx = 0;
        double res = 0;
        for(int i = 0; i < 15; ++i) {
            if(best[i] > res) {
                res = best[i];
                idx = i;
            }
        }
        printf("The safest point is (%.1f, %.1f).\n", tp[idx].x, tp[idx].y);
    }
    return 0;
}

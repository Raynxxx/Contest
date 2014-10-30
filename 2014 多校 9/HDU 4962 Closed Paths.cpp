/*
** HDU 4962 Closed Paths
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
const int INF = 0x3F3F3F3F;
const double EPS = 1e-8;

struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    void read()
    {
        scanf("%d%d", &x, &y);
    }
};

struct Segment
{
    Point a, b;
    double x;
    Segment() {}
    Segment(Point a, Point b) :
        a(a), b(b) {}
    Segment(Point a, Point b, double x) :
        a(a), b(b), x(x) {}
    bool operator < (const Segment& b) const
    {
        return x < b.x;
    }
};

double Cross(Point A, Point B)
{
    return (double)A.x*B.y - (double)A.y*B.x;
}

Point p[MAXN];
Segment seg[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            p[i].read();
        }
        for(int i = 0; i < n; ++i) {
            seg[i] = Segment(p[i], p[(i+1)%n]);
        }
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(seg[i].a.y == 0 && seg[i].b.y == 0) {
                if(seg[i].a.x > seg[i].b.x) {
                    swap(seg[i].a, seg[i].b);
                }
                seg[i].x = (double)seg[i].a.x;
                seg[cnt++] = seg[i];
            } else if((seg[i].a.y >= 0 && seg[i].b.y >= 0) || (seg[i].a.y < 0 && seg[i].b.y < 0)) {
                continue;
            } else {
                seg[i].x = Cross(seg[i].a, seg[i].b) / ((double)seg[i].b.y - seg[i].a.y);
                seg[cnt++] = seg[i];
            }
        }
        sort(seg, seg+cnt);
        int res = 0, tag = 0;
        double right = -INF;
        for(int i = 0; i < cnt; ++i)
        {
            if(seg[i].x > right + EPS && res < tag) {
                right = seg[i].x;
                res = tag;
            }
            if(seg[i].a.y == seg[i].b.y) {
                if((double)seg[i].b.x > right + EPS) {
                    right = (double)seg[i].b.x;
                }
            } else if(seg[i].a.y > seg[i].b.y) {
                tag++;
            } else {
                tag--;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}

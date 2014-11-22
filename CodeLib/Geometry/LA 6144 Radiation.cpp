/*
** LA 6144 Radiation
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 200010;

struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}

    void read()
    {
        scanf("%d%d", &x, &y);
    }
} p[maxn];

int da[maxn], db[maxn];

int Dist2(Point a, Point b)
{
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, Q, cases = 0;
    int ax, ay, bx, by;
    int r1, r2, res;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            p[i].read();
        }
        scanf("%d%d%d%d", &ax, &ay, &bx, &by);
        Point c1(ax, ay), c2(bx, by);
        for(int i = 0; i < n; ++i)
        {
            da[i] = Dist2(p[i], c1);
            db[i] = Dist2(p[i], c2);
        }
        sort(da, da+n);
        sort(db, db+n);
        scanf("%d", &Q);
        printf("Case %d:\n", ++cases);
        while(Q--)
        {
            scanf("%d%d", &r1, &r2);
            int in1 = upper_bound(da, da+n, r1*r1) - da;
            int in2 = upper_bound(db, db+n, r2*r2) - db;
            res = max(n-(in1+in2), 0);
            printf("%d\n", res);
        }
    }
    return 0;
}

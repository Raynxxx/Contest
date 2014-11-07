/*
** CF 166B Polygons
** Created by Rayn @@ 2014/08/08
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const double DINF = 1e20;
const int maxn = 200005;

struct Point
{
    long long x, y;
    bool isb;
    Point() {}
    Point(LL x, LL y): x(x), y(y) {}
    Point(LL x, LL y, bool isb): x(x), y(y), isb(isb) {}

    Point operator + (const Point& p) const
    {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) const
    {
        return Point(x-p.x, y-p.y);
    }
    bool operator < (const Point& p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    void read()
    {
        scanf("%I64d%I64d", &x, &y);
        isb = false;
    }
};

typedef Point Vector;

LL Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
int ConvexHull(Point ch[], Point p[], int n)
{
    sort(p, p+n);

    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; --i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}

Point p[maxn], ch[maxn];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, m;

    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            p[i].read();
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i)
        {
            p[n+i].read();
            p[n+i].isb = true;
        }
        int s = ConvexHull(ch, p, n+m);
        bool flag = true;
        for(int i = 0; i < s; ++i)
        {
            if(ch[i].isb) {
                flag = false;
                break;
            }
        }
        if(flag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

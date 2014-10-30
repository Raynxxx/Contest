/*
** HDU 4946 Area of Mushroom
** Created by Rayn @@ 2014/08/25
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 512;

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();

    int x = 0;
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}

struct Point
{
    int id;
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point(int id, int x, int y): id(id), x(x), y(y) {}

    bool operator < (const Point& p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    Point operator + (const Point& p) const
    {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point& p) const
    {
        return Point(x - p.x, y - p.y);
    }
};

typedef Point Vector;

int Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
int ConvexHull(Point* ch, Point *p, int n)
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
    if(n > 1) m--;
    return m;
}

int n;
bool ok[MAXN];
int x[MAXN], y[MAXN], v[MAXN];
map<PII, int> times;
Point point[MAXN], ch[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T = 0;
    while(scanf("%d%*c", &n) != EOF && n)
    {
        int maxv = 0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &x[i], &y[i], &v[i]);
            maxv = max(maxv, v[i]);
        }
        printf("Case #%d: ", ++T);
        if(maxv == 0)
        {
           for(int i = 0; i < n; ++i) {
                printf("0");
           }
            printf("\n");
            continue;
        }
        times.clear();
        memset(ok, false, sizeof(ok));
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            if(v[i] == maxv)
            {
                times[make_pair(x[i], y[i])]++;
                if(times[make_pair(x[i], y[i])] == 1)
                {
                    point[cnt++] = Point(i, x[i], y[i]);
                }

            }
        }
        int m = ConvexHull(ch, point, cnt);
        for(int i = 0; i < m; ++i)
        {
            ok[ch[i].id] = true;
        }
        for(int i = 0; i < n; ++i)
        {
            if(ok[i] && times[make_pair(x[i], y[i])] == 1) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
    return 0;
}

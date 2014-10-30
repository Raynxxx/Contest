/*
** HDU 4978 A simple probability problem
** Created by Rayn @@ 2014/08/29
*/
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
const int MAXN = 128;
const double PI = acos(-1.0);

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

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
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
};

typedef Point Vector;

inline double sqr(double x)
{
    return x * x;
}
inline double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
inline double Dist(Point A, Point B)
{
    return sqrt(sqr(A.x-B.x) + sqr(A.y-B.y));
}
inline int ConvexHull(Point* ch, Point *p, int n)
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
    if(n > 1) m--;
    return m;
}

int N;
double D;
Point point[MAXN];
Point ch[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%lf", &N, &D);
        for(int i = 0; i < N; ++i) {
            point[i].read();
        }
        printf("Case #%d: ", ++cases);
        if(N <= 1) {
            printf("0.0000\n");
        } else if(N == 2) {
            double len = Dist(point[0], point[1]);
            printf("%.4f\n", (2 * len) / (PI * D));
        } else {
            int m = ConvexHull(ch, point, N);
            double C = 0;
            for(int i = 0; i < m; ++i) {
                C += Dist(ch[i], ch[(i+1)%m]);
            }
            printf("%.4f\n", C / (PI * D));
        }
    }
    return 0;
}

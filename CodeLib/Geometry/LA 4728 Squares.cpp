/*
** LA 4728 Squares
** Created by Rayn @@ 2014/06/17
** 开始尝试用vector来写凸包, 善用STL还是很不错的
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-10;

struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}

    bool operator < (const Point& rhs) const
    {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    bool operator == (const Point& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
    Point operator + (const Point& rhs)
    {
        return Point(x+rhs.x, y+rhs.y);
    }
    Point operator - (const Point& rhs)
    {
        return Point(x-rhs.x, y-rhs.y);
    }
    void getPointInput()
    {
        scanf("%d%d", &x, &y);
    }
    void PointOutput()
    {
        printf("%d %d\n", x, y);
    }
};

typedef Point Vector;

double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
int Dis2(const Point& A, const Point& B)
{
    return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}
vector<Point> ConvexHull(vector<Point>& p)
{
    //去除重复点，会修改输入点集，慎用
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int n = p.size(), m = 0;
    vector<Point> ch(n+1);
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
    ch.resize(m);
    return ch;
}
/* 旋转卡壳求凸包最远点对距离的平方 */
int Solve(vector<Point>& p)
{
    vector<Point> ch = ConvexHull(p);
    int n = ch.size();
    if(n == 1)
        return 0;
    if(n == 2)
        return Dis2(ch[0], ch[1]);
    int ans = 0;
    for(int i = 0, j = 1; i < n; ++i)
    {
        while(Cross(ch[i+1]-ch[i], ch[j+1]-ch[i]) > Cross(ch[i+1]-ch[i], ch[j]-ch[i]))
            j = (j + 1) % n;
        ans = max(ans, max(Dis2(ch[i], ch[j]), Dis2(ch[i+1], ch[j])));
    }
    return ans;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int t, n, x, y, w;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        vector<Point> point;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &x, &y, &w);
            point.push_back(Point(x, y));
            point.push_back(Point(x+w, y));
            point.push_back(Point(x, y+w));
            point.push_back(Point(x+w, y+w));
        }
        printf("%d\n", Solve(point));
    }
    return 0;
}

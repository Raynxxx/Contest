/*
** POJ 3335 Rotating Scoreboard
** Created by Rayn @@ 2014/06/22
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double INF = 1e20;
const double EPS = 1e-10;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    bool operator < (const Point& rhs) const
    {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    bool operator == (const Point& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
    void PointOutput()
    {
        printf("%d %d\n", x, y);
    }
};

typedef Point Vector;

Vector operator + (const Point& A, const Point& B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Point& A, const Point& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
Vector operator * (const Vector& A, double p)
{
    return Vector(A.x*p, A.y*p);
}

struct Line
{
    Point P;
    Vector v;
    double angle;
    Line() {}
    Line(Point P, Vector v): P(P), v(v)
    {
        angle = atan2(v.y, v.x);
    }
    bool operator < (const Line& rhs) const
    {
        return angle < rhs.angle;
    }
};

double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}

bool OnLeft(const Line& L, const Point& p)
{
    //加个=符号，在线上的话也算在左边
    return Cross(L.v, p-L.P) >= 0;
}
Point GetLineIntersection(const Line& a, const Line& b)
{
    Vector u = a.P-b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
vector<Point> HalfPlaneIntersection(vector<Line> L)
{
    int n = L.size();
    sort(L.begin(), L.end());   //按极角排序

    int first, last;
    vector<Line> q(n);
    vector<Point> point(n); //point[i]为q[i]和q[i+1]的交点
    vector<Point> ans;

    q[first=last=0] = L[0]; //双端队列初始化为只有一个半平面L[0]
    for(int i = 1; i < n; ++i)
    {
        while(first < last && !OnLeft(L[i], point[last-1]))
            last--;
        while(first < last && !OnLeft(L[i], point[first]))
            first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < EPS)  //两向量平行且同向，取内侧的一个
        {
            last--;
            if(OnLeft(q[last], L[i].P))
                q[last] = L[i];
        }
        if(first < last)
            point[last-1] = GetLineIntersection(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], point[last-1]))
        last--; //删除无用平面
    if(last - first <= 1)
        return ans; //返回空集

    point[last] = GetLineIntersection(q[first], q[last]);   //计算首尾两个半平面的交点
    for(int i = first; i <= last; ++i)
        ans.push_back(point[i]);
    return ans;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn

    int t, n;
    double x, y;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        vector<Point> p;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }
        reverse(p.begin()+1, p.end());
        vector<Line> line;
        for(int i = 0; i < n; ++i)
        {
            line.push_back(Line(p[i], p[(i+1)%n]-p[i]));
        }
        vector<Point> heart = HalfPlaneIntersection(line);
        //printf("%d\n", heart.size());
        if(heart.size() < 1)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}

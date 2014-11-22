/*
** LA 3890 Most Distant Point from the Sea
** Created by Rayn @@ 2014/06/18
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double INF = 1e20;
const double EPS = 1e-8;

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

double Dot(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y;
}
double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
double Length(const Vector& A)
{
    return sqrt(Dot(A, A));
}
Vector Normal(const Vector& A)
{
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
double PolygonArea(vector<Point> p)
{
    int n = p.size();
    double area = 0;
    for(int i = 1; i < n-1; i++)
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}
bool OnLeft(const Line& L, const Point& p)
{
    return Cross(L.v, p-L.P) > 0;
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

    int first, last;    //双端队列的队首和队尾的下标
    vector<Line> q(n);  //双端队列
    vector<Point> point(n); //point[i]为q[i]和q[i+1]的交点
    vector<Point> ans; //保存结果

    q[first=last=0] = L[0]; //双端队列初始化为只有一个半平面L[0]
    for(int i = 1; i < n; ++i)
    {
        while(first < last && !OnLeft(L[i], point[last-1]))
            last--;
        while(first < last && !OnLeft(L[i], point[first]))
            first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < EPS)   //两向量平行且同向，取内侧的一个
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
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n;
    double x, y;

    while(scanf("%d", &n) != EOF && n)
    {
        vector<Point> p, v, normal;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }
        if(PolygonArea(p) < 0)
            reverse(p.begin(), p.end());

        for(int i = 0; i < n; ++i)
        {
            v.push_back(p[(i+1)%n]-p[i]);
            normal.push_back(Normal(v[i]));
        }
        double left = 0, right = 10000;
        while(left + EPS < right)
        {
            vector<Line> L;
            double mid = left + (right-left)/2;
            for(int i = 0; i < n; ++i)
            {
                L.push_back(Line(p[i]+normal[i]*mid, v[i]));
            }
            vector<Point> poly = HalfPlaneIntersection(L);
            if(poly.empty())
                right = mid;
            else
                left = mid;
        }
        printf("%.6f\n", left);
    }
    return 0;
}

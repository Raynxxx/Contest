/*
** POJ 1755 Triathlon
** Created by Rayn @@ 2014/07/08
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;
const double INF = 1e12;
const int MAXN = 220;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    bool operator == (const Point& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator < (const Point& rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};
typedef Point Vector;

Vector operator + (const Point& a, const Point& b)
{
    return Vector(a.x+b.x, a.y+b.y);
}
Vector operator - (const Point& a, const Point& b)
{
    return Vector(a.x-b.x, a.y-b.y);
}
Vector operator * (const Vector& v, const double& p)
{
    return Vector(v.x*p, v.y*p);
}
int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x > 0)? 1 : -1;
}
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
double Dis(const Vector& A, const Vector& B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}
Vector Normal(const Vector& A)
{
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
struct Line
{
    Point P;
    Vector v;
    double angle;
    Line() {}
    Line(Point p1, Point p2): P(p1)
    {
        v = p2 - p1;
        angle = atan2(v.y, v.x);
    }
    bool operator < (const Line& rhs) const
    {
        return angle < rhs.angle;
    }
};

bool OnLeft(const Line& L, const Point& p)
{
    return Cross(L.v, p-L.P) > 0;
}
Point GetLineIntersection(const Line& a, const Line& b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
vector<Point> HalfplaneIntersection(vector<Line> L)
{
    int n = L.size();
    sort(L.begin(), L.end());

    int first, last;
    vector<Line> q(n);
    vector<Point> point(n);
    vector<Point> ans;

    q[first=last=0] = L[0];
    for(int i = 1; i < n; ++i)
    {
        while(first < last && !OnLeft(L[i], point[last-1]))
            last--;
        while(first < last && !OnLeft(L[i], point[first]))
            first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < EPS)
        {
            last--;
            if(OnLeft(q[last], L[i].P))
                q[last] = L[i];
        }
        if(first < last)
            point[last-1] = GetLineIntersection(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], point[last-1]))
        last--;
    if(last - first <= 1)
        return ans;

    point[last] = GetLineIntersection(q[first], q[last]);
    for(int i = first; i <= last; ++i)
        ans.push_back(point[i]);
    return ans;
}

int n;
int v[MAXN], u[MAXN], w[MAXN];

bool Solve(int now)
{
    double A, B, C;
    double x1, y1, x2, y2;

    vector<Line> line;
    line.reserve(MAXN);
    line.push_back(Line(Point(0.0, 0.0), Point(INF, 0.0)));
    line.push_back(Line(Point(INF, 0.0), Point(INF, INF)));
    line.push_back(Line(Point(INF, INF), Point(0.0, INF)));
    line.push_back(Line(Point(0.0, INF), Point(0.0, 0.0)));
    for(int i = 0; i < n; ++i)
    {
        if(i == now)
            continue;
        A = 1.0/v[i] - 1.0/v[now];
        B = 1.0/u[i] - 1.0/u[now];
        C = 1.0/w[i] - 1.0/w[now];
        /*
        A = (v[i] - v[now]) / (v[i] * v[now]);
        B = (u[i] - u[now]) / (u[i] * u[now]);
        C = (w[i] - w[now]) / (w[i] * w[now]);
        */
        //转换为 Ax+By+C>0, 然后在Ax+By+C=0直线上取两点构成向量
        //再用半平面交判断是否有解。
        if(!dcmp(A))
        {
            if(!dcmp(B))
            {
                if(dcmp(C) <= 0)
                    return false;
            }
            else
            {
                x1 = 0; x2 = dcmp(B);
                y1 = y2 = -C/B;
            }
        }
        else
        {
            if(!dcmp(B))
            {
                x1 = x2 = -C/A;
                y1 = 0; y2 = -dcmp(A);
            }
            else
            {
                x1 = 0; y1 = -C/B;
                x2 = dcmp(B); y2 = -(A*x2 + C) / B;
            }
        }
        line.push_back(Line(Point(x1, y1), Point(x2, y2)));
    }
    return HalfplaneIntersection(line).size();
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &v[i], &u[i], &w[i]);
    }
    for(int i = 0; i < n; ++i)
    {
        if(Solve(i))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

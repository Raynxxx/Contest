/*
** POJ 3384 Feng Shui
** Created by Rayn @@ 2014/06/25
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;

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
    Line(Point P, Vector v): P(P), v(v)
    {
        angle = atan2(v.y, v.x);
    }
    bool operator < (const Line& rhs) const
    {
        return angle < rhs.angle;
    }
};

bool OnLeft(const Line& L, const Point& p)
{
    //尼玛边上的点又要算上，想想也对。。。是我傻逼了
    return Cross(L.v, p-L.P) >= 0;
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
Point c1, c2;
void Solve(vector<Point> p)
{
    int n = p.size();
    if(n == 1)
    {
        c1 = c2 = p[0];
        return ;
    }
    double maxdis = -1;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            double dis = Dis(p[i], p[j]);
            if(dis + EPS > maxdis)
            {
                maxdis = dis;
                c1 = p[i];
                c2 = p[j];
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, r;
    double x, y;

    while(scanf("%d%d", &n, &r) != EOF)
    {
        vector<Point> p, v, normal, ans;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }
        reverse(p.begin(), p.end());
        for(int i = 0; i < n; ++i)
        {
            v.push_back(Point(p[(i+1)%n]-p[i]));
            normal.push_back(Normal(v[i]));
        }
        vector<Line> line;
        for(int i = 0; i < n; ++i)
        {
            line.push_back(Line(p[i]+normal[i]*r, v[i]));
        }
        ans = HalfplaneIntersection(line);
        Solve(ans);
        printf("%.4f %.4f %.4f %.4f\n", c1.x, c1.y, c2.x, c2.y);
    }
    return 0;
}


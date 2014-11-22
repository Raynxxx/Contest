/*
** POJ 2540 Hotter Colder
** Created by Rayn @@ 2014/07/08
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-5;
const double INF = 1e12;
const int MAXN = 120;

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
Vector operator / (const Vector& v, const double& p)
{
    return Vector(v.x/p, v.y/p);
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
    Line(Point p, Vector v): P(p), v(v)
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
    return Cross(L.v, p-L.P) > 0;
}
Point GetLineIntersection(const Line& a, const Line& b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
vector<Point> HalfplaneIntersection(vector<Line>& L)
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
double PolygonArea(vector<Point>& p)
{
    int n = p.size();
    double sum = 0;
    for(int i = 1; i < n-1; i++)
    {
        sum += Cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return sum/2;
}

map<string, int> mp;
vector<Point> p, ans;
vector<Line> line;

void Init()
{
    mp["Hotter"] = 1;
    mp["Colder"] = 2;
    mp["Same"] = 3;

    p.reserve(MAXN);
    p.push_back(Point(0, 0));
    Point p1(0, 0), p2(10, 0), p3(10, 10), p4(0, 10);
    line.reserve(MAXN);
    line.push_back(Line(p1, p2-p1));
    line.push_back(Line(p2, p3-p2));
    line.push_back(Line(p3, p4-p3));
    line.push_back(Line(p4, p1-p4));
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    double x, y, area;
    char id[10];
    Vector nor;

    Init();
    int pre = -1, now = 0;
    bool flag = false;
    while(scanf("%lf%lf%s", &x, &y, id) != EOF)
    {
        p.push_back(Point(x, y));
        pre++; now++;

        Point mid = (p[now] + p[pre]) / 2.0;
        if(mp[id] == 1)
        {
            nor = Normal(p[pre]-p[now]);
            line.push_back(Line(mid, nor));
        }
        else if(mp[id] == 2)
        {
            nor = Normal(p[now]-p[pre]);
            line.push_back(Line(mid, nor));
        }
        else if(mp[id] == 3)
        {
            flag = true;
        }
        if(flag)
        {
            printf("0.00\n");
            continue;
        }
        ans = HalfplaneIntersection(line);
        area = PolygonArea(ans);
        if(area == 0.0)
            flag = true;
        if(ans.size() < 3)
            printf("0.00\n");
        else
            printf("%.2f\n", area);
    }
    return 0;
}

/*
** POJ 1474 Video Surveillance
** Created by Rayn @@ 2014/06/22
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

double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
struct Line
{
    Point P;
    Vector v;
    double angle;
    Line() {}
    Line(Point p, Vector v) : P(p), v(v)
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
    return Cross(L.v, p-L.P) >= 0;
}
Point GetLineIntersection(const Line& a, const Line& b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
vector<Point> HalfPlaneIntersection(vector<Line> L)
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
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, cases = 0;
    double x, y;

    while(scanf("%d", &n) != EOF && n)
    {
        vector<Point> p, ans;
        p.reserve(105);
        ans.reserve(105);
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }
        vector<Line> line;
        for(int i = 0; i < n; ++i)
        {
            line.push_back(Line(p[i], p[(i+1)%n]-p[i]));
        }
        ans = HalfPlaneIntersection(line);
        printf("Floor #%d\n", ++cases);
        if(ans.size() < 1)
            printf("Surveillance is impossible.\n\n");
        else
            printf("Surveillance is possible.\n\n");
    }
    return 0;
}

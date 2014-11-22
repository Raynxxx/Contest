/*
** POJ 1279 Art Gallery
** Created by Rayn @@ 2014/06/24
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;
const int MAX = 1510;

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
double Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
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
    /*
    for(Line& tmp : L)
    {
        cout << "P: " << tmp.P.x << " " << tmp.P.y << endl;
        cout << "v: " << tmp.v.x << " " << tmp.v.y << endl;
    }
    */
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
double PolygonArea(vector<Point> p)
{
    int n = p.size();
    double sum = 0;
    for(int i = 1; i < n-1; i++)
    {
        sum += Cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return sum/2;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int t, n;
    double x, y;

    scanf("%d", &t);
    while(t--)
    {
        vector<Point> p, ans;
        p.reserve(MAX);
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf", &x, &y);
            p.push_back(Point(x, y));
        }
        if(PolygonArea(p) < 0)
        {
            reverse(p.begin(), p.end());
        }
        vector<Line> line;
        for(int i = 0; i < n; ++i)
        {
            line.push_back(Line(p[i], p[(i+1)%n]-p[i]));
        }
        ans = HalfplaneIntersection(line);
        //printf("%d\n", ans.size());
        printf("%.2f\n", PolygonArea(ans));
    }
    return 0;
}

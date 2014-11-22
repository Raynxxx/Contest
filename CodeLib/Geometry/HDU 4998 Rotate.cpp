/*
** HDU 4998 Rotate
** Created by Rayn @@ 2014/09/14
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 20;
const double EPS = 1e-8;
const double INF = 1e3;
const double PI = acos(-1.0);

double dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y):
        x(x), y(y) {}
    bool operator == (const Point& p) const {
        return (dcmp(x-p.x) == 0 && dcmp(y-p.y) == 0);
    }
    Point operator + (const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double& p) const {
        return Point(x*p, y*p);
    }
    Point operator / (const double& p) const {
        return Point(x/p, y/p);
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    void print()
    {
        printf("%.10f %.10f\n", x, y);
    }
};
typedef Point Vector;

double Dot(Point A, Point B)
{
    return A.x*B.x + A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A, A));
}
double Cross(Point A, Point B)
{
    return A.x*B.y - A.y*B.x;
}
double Angle(Vector A, Vector B)
{
    return acos(Dot(A, B) / Length(A) / Length(B));
}
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}
Vector Normal(Vector A)
{
    return Vector(-A.y, A.x);
}
Vector reNormal(Vector A)
{
    return Vector(A.y, A.x);
}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-b1, a1-b1), d2 = Cross(a2-b2, a1-b2);
    double d3 = Cross(b1-a1, b2-a1), d4 = Cross(b1-a2, b2-a2);
    return dcmp(d1) * dcmp(d2) < 0 && dcmp(d3) * dcmp(d4) < 0;
}
Point getLineIntersection(Point P, Vector v, Point Q, Vector w)
{
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
bool Intersection(Point p1, Point p2, Point q1, Point q2, Point& is)
{
	double m = Cross(q2-q1, p1-q1);
	double n = Cross(q2-q1, p2-q1);
	if(dcmp(n-m) == 0)
        return false;
	is = (p1*n - p2*m) / (n - m);
	return true;
}

Point a[MAXN];
double pi[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        double ang = 0;
        for(int i = 1; i <= n; ++i) {
            a[i].read();
            scanf("%lf", &pi[i]);
            ang += pi[i];
            if(ang + EPS > 2 * PI) {
                ang -= 2 * PI;
            }
        }
        Point A(INF, -INF), B(INF, INF), C(INF+INF, INF);
        Point PA = A, PB = B, PC = C, inter;
        Vector v1, v2, v3;
        for(int i = 1; i <= n; ++i)
        {
            v1 = Rotate(PA - a[i], pi[i]);
            v2 = Rotate(PB - a[i], pi[i]);
            v3 = Rotate(PC - a[i], pi[i]);
            PA = a[i] + v1;
            PB = a[i] + v2;
            PC = a[i] + v3;
        }
        Point mid1 = (A + PA) / 2.0;
        Point mid2 = (B + PB) / 2.0;
        Point mid3 = (C + PC) / 2.0;
        v1 = Normal(PA-A);
        v2 = Normal(PB-B);
        v3 = Normal(PC-C);
        if(dcmp(Cross(v1, v2)) != 0) {
            inter = getLineIntersection(mid1, v1, mid2, v2);
        } else {
            inter = getLineIntersection(mid1, v1, mid3, v3);
        }
        printf("%.8f %.8f %.8f\n", inter.x, inter.y, ang);
    }
    return 0;
}

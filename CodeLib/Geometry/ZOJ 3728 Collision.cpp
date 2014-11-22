/*
** ZOJ 3728 Collision
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;
const double EPS = 1e-12;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
};

typedef Point Vector;

inline double sqr(double x)
{
    return x * x;
}
inline double Dot(Point A, Point B)
{
    return A.x*B.x + A.y*B.y;
}
inline double Length(Vector A)
{
    return sqrt(Dot(A, A));
}
inline double Cross(Point A, Point B)
{
    return A.x*B.y - A.y*B.x;
}
inline double Dist(Point A, Point B)
{
    return sqrt(sqr(A.x-B.x) + sqr(A.y-B.y));
}

double Rm, R, r;
double x, y, vx, vy;
Point coin, speed;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
	while(scanf("%lf%lf%lf%lf%lf%lf%lf", &Rm, &R, &r, &x, &y, &vx, &vy) != EOF)
    {
        coin = Point(x, y);
        speed = Vector(vx, vy);
        if(Dot(coin, speed) >= EPS) {
            printf("0.000\n");
            continue;
        }
        double v = Length(speed);
        double H = fabs(Cross(coin, speed) / v);
        double res;
        if(H >= R + r + EPS) {
            printf("0.000\n");
            continue;
        } else if(H >= Rm + r + EPS) {
            res = sqrt(sqr(R + r) - sqr(H)) * 2.0;
        } else {
            res = sqrt(sqr(R + r) - sqr(H)) - sqrt(sqr(Rm + r) - sqr(H));
            res *= 2.0;
        }
        printf("%.5f\n", res / v);
	}
	return 0;
}

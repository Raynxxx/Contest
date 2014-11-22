/*
** HDU 5017 Ellipsoid
** Created by Rayn @@ 2014/09/18s
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const double INF = 1e5;
const double EPS = 1e-16;

double a, b, c, d, e, f;

inline double Square(double x)
{
    return x * x;
}
double getZ(double A, double B, double C)
{
    if(Square(B) - 4 * A * C < EPS) {
        return INF;
    }
    return (sqrt(Square(B) - 4 * A * C) - B) / (2 * A);
}
double CalFunc(double x, double y)
{
    double z = getZ(c, e*x + d*y, a*x*x + b*y*y + f*x*y - 1);
    return Square(x) + Square(y) + Square(z);
}
double nextGao(double x)
{
    double l = -INF, r = INF;
    for(int i = 0; i < 200; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(CalFunc(x, m1) > CalFunc(x, m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    return CalFunc(x, l);
}
double Gao(double l, double r)
{
    for(int i = 0; i < 200; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(nextGao(m1) > nextGao(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    return sqrt(nextGao(l));
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF) {
        printf("%.6f\n", Gao(-INF, INF));
    }
    return 0;
}

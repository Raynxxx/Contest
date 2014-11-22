/*
** ZOJ 3733 Skycity
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const double EPS = 1e-8;
const double PI = acos(-1.0);

double Gao(double r, double h, double S)
{
    int left = 3, right = 1e5;
    double ret = 0;
    while(left < right)
    {
        int mid = (left + right + 1) >> 1;
        double theta = PI / mid;
        double area = (2 * r * tan(theta)) * h;
        if(area >= S + EPS) {
            left = mid;
            ret = area * mid;
        } else {
            right = mid - 1;
        }
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    double R, r, H, F, S;
	while(scanf("%lf%lf%lf%lf%lf", &R, &r, &H, &F, &S) != EOF)
    {
        double height = H / F, dr = (R - r) / F, radius = r;
        double res = 0;
        for(int i = 1; i <= F; ++i)
        {
            res += Gao(radius, height, S);
            radius += dr;
        }
        printf("%.6f\n", res);
	}
	return 0;
}

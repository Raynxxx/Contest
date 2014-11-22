/*
** ZOJ 3334 Body Check
** Created by Rayn @@ 2014/07/05
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;

int m, n;
double a[1010];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
bool Judge(double time)
{
    double tmp = 0;
    for(int i = 0; i < n; ++i)
    {
        tmp += min(time, a[i]);
    }
    if(dcmp(tmp - time*m) < 0)
        return true;
    return false;
}
int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &m, &n)!=EOF)
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf", &a[i]);
            sum += a[i];
        }
        double L = 0, R = sum;
        while(dcmp(R-L) > 0)
        {
            double mid = (L + R) / 2;
            if(Judge(mid))
                R = mid;
            else
                L = mid;
        }
        //printf("%.9f\n", L);
        printf("%.10f\n", sum-(m-1)*L);
    }
    return 0;
}

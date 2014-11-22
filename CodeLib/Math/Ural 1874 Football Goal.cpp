/*
** Ural 1874 Football Goal
** Created by Rayn @@ 2014/05/25
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define EPS 1e-10
using namespace std;

double a, b;

double GetS(double k)
{
    double p = (a + b + k) / 2;
    return k*k/4 + sqrt(p*(p-a)*(p-b)*(p-k));
}
int main()
{
    scanf("%lf%lf", &a, &b);
    double l = 0 , r = a + b;
    while(l + EPS < r)
    {
        double m1 = l + (r - l)/3;
        double m2 = r - (r - l)/3;
        if(GetS(m1) >= GetS(m2))
            r = m2;
        else
            l = m1;
    }
    printf("%.9f\n", GetS(l));
    return 0;
}

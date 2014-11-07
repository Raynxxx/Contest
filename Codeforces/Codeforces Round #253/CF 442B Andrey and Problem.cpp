/*
** CF 442B Andrey and Problem
** Created by Rayn @@ 2014/10/04
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 105;

double p[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) {
            scanf("%lf", &p[i]);
        }
        sort(p, p + n, greater<double>());
        double ret = 0.0;
        for(int i = 1; i <= n; ++i) {
            double one = 0;
            for(int j = 0; j < i; ++j) {
                double s = p[j];
                for(int k = 0; k < i; ++k) {
                    if(k != j) {
                        s *= (1 - p[k]);
                    }
                }
                one += s;
            }
            ret = max(ret, one);
        }
        printf("%.12f\n", ret);
    }
    return 0;
}

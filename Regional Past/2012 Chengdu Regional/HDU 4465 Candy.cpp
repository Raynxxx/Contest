/*
** HDU 4465 Candy
** Created by Rayn @@ 2014/10/03
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

double Gao(int n, double p, double q) {
    double ret = n * p, step = 1.0;
    for(int i = 1; i <= n; ++i) { //take i candy in the second box
        step *= p * q * (n + i) / i;
        ret += step * (n - i);
        ret *= p;
    }
    return ret;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, cases = 0;
    double p;
    while(scanf("%d%lf", &n, &p) != EOF) {
        double ret = Gao(n, p, 1-p) + Gao(n, 1-p, p);
        printf("Case %d: %.6f\n", ++cases, ret);
    }
    return 0;
}

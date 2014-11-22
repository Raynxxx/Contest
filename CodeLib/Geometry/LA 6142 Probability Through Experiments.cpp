/*
** LA 6142 Probability Through Experiments
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 20010;
const double EPS = 1e-8;

double delta[maxn];

int dcmp(double x)
{
    if(fabs(x) < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, r, cases = 0;
    while(scanf("%d%d", &n, &r) != EOF)
    {
        if(n == 0 && r == 0)
            break;
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf", &delta[i]);
        }
        sort(delta, delta+n);
        LL res = (LL)n * (n-1) * (n-2) / 6;
        LL t;
        for(int i = 0; i < n; ++i)
        {
            if(dcmp(delta[i]-180) < 0)
                t = lower_bound(delta, delta+n, delta[i]+180+EPS) - delta - i - 1;
            else
                t = lower_bound(delta, delta+n, delta[i]-180+EPS) - delta - i - 1 + n;
            res -= t * (t-1) / 2;
        }
        printf("Case %d: %lld\n", ++cases, res);
    }
    return 0;
}

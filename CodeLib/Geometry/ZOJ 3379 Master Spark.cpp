/*
** ZOJ 3379 Master Spark
** Created by Rayn @@ 2014/08/20
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#define sqr(x) ((x)*(x))
using namespace std;
const int MAXN = 30010;
const double PI = M_PI;

double a;
double x[MAXN], y[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d%lf", &n, &a) != EOF)
    {
        vector<pair<double, double> > range;
        priority_queue<double, vector<double>, greater<double> > pq;

        for(int i = 0; i < n; ++i)
        {
            scanf("%lf", &x[i]);
        }
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf", &y[i]);
        }
        for(int i = 0; i < n; ++i)
        {
            double t = atan2(y[i], x[i]);
            double z = sqr(x[i]) + sqr(y[i]);
            double d = sqrt((sqrt(1 + 4*sqr(a)*z) - 1) / (2 * sqr(a)));
            d = atan2(1, a * d);
            range.push_back(make_pair(remainder(t-d, 2*PI), remainder(t+d, 2*PI)));
            if(range.back().first > range.back().second)
            {
                pq.push(range.back().second);
                range.back().second += 2*PI;
            }
        }
        int res = (int) pq.size();
        sort(range.begin(), range.end());
        vector<pair<double, double> >::const_iterator it;
        for(it = range.begin(); it != range.end(); ++it)
        {
            pq.push(it->second);
            while(!pq.empty() && pq.top() < it->first)
            {
                pq.pop();
            }
            res = max(res, (int) pq.size());
        }
        printf("%d daze\n", res);
    }
    return 0;
}

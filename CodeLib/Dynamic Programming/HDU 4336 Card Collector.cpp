/*
** HDU 4336 Card Collector
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;

double p[MAXN];
double dp[1<<20];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%lf", &p[i]);
        }
        double ret = 0;
        for(int s = 1; s < (1 << n); ++s) {
            int cnt = 0;
            double sum = 0.0;
            for(int i = 0; i < n; ++i) {
                if((1 << i) & s) {
                    cnt++;
                    sum += p[i];
                }
            }
            if(cnt & 1) ret += 1.0 / sum;
            else ret -= 1.0 / sum;
        }
        printf("%.5f\n", ret);
    }
    return 0;
}

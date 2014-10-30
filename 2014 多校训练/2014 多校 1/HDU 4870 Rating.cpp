/*
** HDU 4870 Rating
** Created by Rayn @@ 2014/07/24
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    double p, q, sum;
    double dp[21];

    while(scanf("%lf", &p) != EOF)
    {
        q = 1 - p;

        dp[0] = 1 / p;
        dp[1] = 1 + q/p * (1 + dp[0]);
        sum = (dp[0] + dp[1]) * 2;
        for(int i = 2; i < 20; ++i)
        {
            dp[i] = 1 + q/p * (1 + dp[i-1] + dp[i-2]);
            sum += dp[i] * 2;
        }
        sum -= dp[19];
        printf("%.6f\n", sum);
    }
    return 0;
}

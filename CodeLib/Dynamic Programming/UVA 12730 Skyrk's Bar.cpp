/*
** UVA 12730 Skyrk's Bar
** Created by Rayn @@ 2014/10/01
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 1000005;

int N, K;
double dp[MAXN];
double sum[MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &K);
        sum[0] = 0;
        for(int i = 1; i <= N; ++i) {
            if(i <= K + 1) {
                dp[i] = 1.0;
            } else {
                dp[i] = 2.0 * sum[i-K-1] / i + 1.0;
            }
            sum[i] = sum[i-1] + dp[i];
        }
        printf("Case #%d: %.4f\n", ++cases, dp[N]);
    }
    return 0;
}

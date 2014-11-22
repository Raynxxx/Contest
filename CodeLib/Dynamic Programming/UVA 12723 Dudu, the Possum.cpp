/*
** UVA 12723 Dudu, the Possum
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
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 600;

int N, K;
double P[MAXN];
double eat[MAXN];
double dp[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &K);
        for(int i = 1; i <= K; ++i) {
            scanf("%lf", &P[i]);
        }
        fill(eat, eat + MAXN, 0.0);
        fill(dp, dp + MAXN, 0.0);
        for(int i = 1; i <= N; ++i) {
            int Qi;
            scanf("%d", &Qi);
            for(int j = 1; j <= Qi; ++j) {
                double c, x;
                scanf("%lf%lf", &c, &x);
                eat[i] += c * x;
            }
        }
        for(int i = N; i >= 1; --i) {
            dp[i] += eat[i];
            for(int j = 1; j <= K; ++j) {
                dp[i] += P[j] * dp[i + j];
            }
        }
        printf("Case #%d: %.6f\n", ++cases, dp[1]);
    }
    return 0;
}

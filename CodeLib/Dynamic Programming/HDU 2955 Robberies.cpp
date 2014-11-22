/*
** HDU 2955 Robberies
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 128;

int N, M[MAXN];
double SP, P[MAXN];
double dp[MAXN*MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lf%d", &SP, &N);
        int total = 0;
        for(int i = 1; i <= N; ++i) {
            scanf("%d %lf", &M[i], &P[i]);
            total += M[i];
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int i = 1; i <= N; ++i) {
            for(int j = total; j >= 0; --j) {
                dp[j + M[i]] = max(dp[j + M[i]], dp[j] * (1-P[i]));
            }
        }
        for(int i = total; i >= 0; --i) {
            if(1 - dp[i] < SP) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}

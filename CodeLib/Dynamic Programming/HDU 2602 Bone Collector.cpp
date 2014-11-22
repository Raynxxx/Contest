/*
** HDU 2602 Bone Collector
** Created by Rayn @@ 2014/04/21
** 01背包问题
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1010;

int v[MAX], w[MAX];
int dp[MAX];

int main()
{
    int T, N, V;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &V);
        for(int i=1; i<=N; ++i)
            scanf("%d", &v[i]);
        for(int i=1; i<=N; ++i)
            scanf("%d", &w[i]);

        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=N; ++i)
        {
            for(int j=V; j>=w[i]; --j)
            {
                dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
            }
        }
        printf("%d\n", dp[V]);
    }
    return 0;
}

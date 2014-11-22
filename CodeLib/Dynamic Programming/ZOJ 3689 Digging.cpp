/*
** ZOJ 3689 Digging
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node
{
    int s, t;
    bool operator < (const Node& rhs) const
    {
        return this->s * rhs.t > rhs.s * this->t;
    }
} arr[3010];

int dp[10010];

int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N, T;
    while(scanf("%d%d", &N, &T) != EOF)
    {
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < N; ++i)
        {
            scanf("%d%d", &arr[i].t, &arr[i].s);
        }
        sort(arr, arr+N);
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j <= T; ++j)
            {
                if(j + arr[i].t > T)
                    continue;
                dp[j] = max(dp[j], dp[j+arr[i].t] + (j+arr[i].t)*arr[i].s);
            }
        }
        int ans = 0;
        for(int i = 0; i <= T; ++i)
        {
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
** ZOJ 3640 Help Me Escape
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 10000 + 7;

int n;
int c[107], t[107];
double dp[maxn*2];

void Init()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i)
    {
        t[i] = floor((1+sqrt(5.0))*c[i]*c[i]/2.0);
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int f;
    while (scanf("%d %d", &n, &f) != EOF)
    {
        int maxc = -1;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &c[i]);
            maxc = max(maxc, c[i]);
        }
        Init();
        for (int i = maxc*2; i >= f; --i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i <= c[j])
                    dp[i] += dp[c[j]+i] + 1;
                else
                    dp[i] += t[j];
            }
            dp[i] /= n;
        }
        printf("%.3f\n", dp[f]);
    }
    return 0;
}

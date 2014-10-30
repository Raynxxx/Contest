/*
** HDU 4745 Two Rabbits
** Created by Rayn @@ 2014/09/22
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 1010;

int stone[MAXN];
int dp[MAXN][MAXN];

int Gao(int n)
{
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i) {
        dp[i][i] = 1;
    }
    for(int i = n-1; i >= 1; --i) {
        for(int j = i + 1; j <= n; ++j) {
            dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            if(stone[i] == stone[j]) {
                dp[i][j] = max(dp[i][j], dp[i+1][j-1] + 2);
            }
        }
    }
    int ret = 0;
    for(int i = 1; i <= n; ++i) {
        ret = max(ret, dp[1][i] + dp[i+1][n]);
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &stone[i]);
        }
        printf("%d\n", Gao(n));
    }
    return 0;
}

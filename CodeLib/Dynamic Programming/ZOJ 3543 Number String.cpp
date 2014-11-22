/*
** ZOJ 3543 Number String
** Created by Rayn @@ 2014/09/17
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

typedef long long LL;
const int MAXN = 1024;
const LL MOD = 1000000007;

int dp[MAXN][MAXN];
int sum[MAXN][MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char str[MAXN];
    while(scanf("%s", str + 2) != EOF)
    {
        int n = strlen(str + 2);
        dp[1][1] = sum[1][1] = 1;
        for(int i = 2; i <= n + 1; ++i) {
            for(int j = 1; j <= i; j++) {
                if(str[i] == 'I') {
                    dp[i][j] = sum[i-1][j-1];
                } else if(str[i] == 'D') {
                    dp[i][j] = (sum[i-1][i-1] - sum[i-1][j-1] + MOD) % MOD;
                } else {
                    dp[i][j] = sum[i-1][i-1];
                }
                sum[i][j] = (sum[i][j-1] + dp[i][j]) % MOD;
            }
        }
        printf("%d\n", sum[n+1][n+1]);
    }
    return 0;
}

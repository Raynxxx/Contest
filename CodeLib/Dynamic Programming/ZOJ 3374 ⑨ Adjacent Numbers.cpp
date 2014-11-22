/*
** ZOJ 3374 ⑨ Adjacent Numbers
** Created by Rayn @@ 2014/08/28
** 题解：
** dp[i][0][0] = 1;
** dp[i][j][0] = sum{dp[i-1][j][k] | k < l};
** dp[i][j][k] = dp[i-1][j-1][k-1];
** 由于 dp[i][j][k] = dp[i-k][j-k][0], 其实只要二维就够了
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 1024;
const int MAXM = 9;

int N, M;
double comb[MAXN][MAXN];
double dp[MAXN][MAXN];

void Init()
{
    comb[0][0] = dp[0][0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
    }
    for(int i = 1; i < MAXN; ++i) {
        for(int j = 0; j <= i; ++j) {
            dp[i][j] = 0;
            for(int k = 0; k < MAXM && k <= j && k < i; ++k) {
                dp[i][j] += dp[i-k-1][j-k];
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    double s;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        if(M < MAXM) {
            s = 0;
        } else {
            s = 0;
            for(int i = 0; i < MAXM; ++i) {
                for(int j = 0; i + j < MAXM; ++j) {
                    s += dp[N-i-j-1][M-i-j];
                }
            }
            s = 1 - s / comb[N][M];
        }
        printf("%.6f%%\n", fabs(s*100));
    }
    return 0;
}


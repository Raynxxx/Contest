/*
** ZOJ 3735 Josephina and RPG
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 10010;
const int MAXC = 128;

int N, M, R;
int AL[MAXN];
double T[MAXC][MAXC];
double dp[MAXN][MAXC];
const int comb[] = {0, 0, 0, 1, 4, 10, 20, 35, 56, 84, 120};

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

	while(scanf("%d", &M) != EOF)
    {
        R = comb[M];
        for(int i = 0; i < R; ++i) {
            for(int j = 0; j < R; ++j) {
                scanf("%lf", &T[i][j]);
            }
        }
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &AL[i]);
        }
        memset(dp, 0, sizeof(dp[0])*(N+2));
        for(int i = 0; i < R; ++i) {
            dp[0][i] = 1;
        }
        for(int i = 1; i <= N; ++i) {
            for(int j = 0; j < R; ++j) {
                dp[i][j] = max(dp[i][j], dp[i-1][j] * T[j][AL[i]]);
                dp[i][AL[i]] = max(dp[i][AL[i]], dp[i-1][j] * T[j][AL[i]]);
            }
        }
        double res = 0;
        for(int i = 0; i < R; ++i) {
            res = max(res, dp[N][i]);
        }
        printf("%.6f\n", res);
	}
	return 0;
}

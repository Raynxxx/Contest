/*
** ZOJ 3329 One Person Game
** Created by Rayn @@ 2014/09/15
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

const int MAXN = 560;

int n, K1, K2, K3, a, b, c;
double dp[MAXN], A[MAXN], B[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d%d", &n, &K1, &K2, &K3, &a, &b, &c);
        double one = 1.0 / K1 / K2 / K3;
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= K1; ++i) {
            for(int j = 1; j <= K2; ++j) {
                for(int k = 1; k <= K3; ++k) {
                    if(i != a || j != b || k != c) {
                        dp[i+j+k] += one;
                    }
                }
            }
        }
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        for(int i = n; i >= 0; --i) {
            A[i] = one;
            B[i] = 1;
            for(int j = 1; j <= K1+K2+K3; ++j) {
                A[i] += A[i+j] * dp[j];
                B[i] += B[i+j] * dp[j];
            }
        }
        printf("%.16f\n", B[0] / (1 - A[0]));
    }
    return 0;
}

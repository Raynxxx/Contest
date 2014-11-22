/*
** ZOJ 3541 The Last Puzzle
** Created by Rayn @@ 2014/09/16
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
const int MAXN = 205;
const int INF = 0x3F3F3F3F;

int T[MAXN], D[MAXN];
int dp[MAXN][MAXN][2];
int pre[MAXN][MAXN][2];

int Gao(int l, int r, int p)
{
    int tmp, add;
    int& ret = dp[l][r][p];
    if(ret == -1) {
        if(l == r) {
            ret = 0;
        } else {
            ret = INF;
            tmp = (D[l+1] - D[l]) + Gao(l+1, r, 0);
            add = (p == 0)? 0 : D[r] - D[l];
            if(T[l] > tmp && ret > tmp + add) {
                ret = tmp + add;
                pre[l][r][p] = 0;
            }
            tmp = (D[r] - D[r-1]) + Gao(l, r-1, 1);
            add = (p == 1)? 0 : D[r] - D[l];
            if(T[r] > tmp && ret > tmp + add) {
                ret = tmp + add;
                pre[l][r][p] = 1;
            }
        }
    }
    return ret;
}
void getSolution(int l, int r, int p)
{
    if(l == r) {
        printf("%d\n", l+1);
    } else if(pre[l][r][p] == 0) {
        printf("%d ", l+1);
        getSolution(l+1, r, 0);
    } else if(pre[l][r][p] == 1) {
        printf("%d ", r+1);
        getSolution(l, r-1, 1);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%d", &T[i]);
        }
        for(int i = 0; i < n; ++i) {
            scanf("%d", &D[i]);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                dp[i][j][0] = dp[i][j][1] = -1;
            }
        }
        if(Gao(0, n-1, 0) == INF) {
            printf("Mission Impossible\n");
        } else {
            getSolution(0, n-1, 0);
        }
    }
    return 0;
}

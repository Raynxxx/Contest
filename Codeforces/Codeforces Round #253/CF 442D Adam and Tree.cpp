/*
** CF 442D Adam and Tree
** Created by Rayn @@ 2014/10/04
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int fa[MAXN];
int dp[MAXN];
int max1[MAXN];
int max2[MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 2; i <= n + 1; ++i) {
            scanf("%d", &fa[i]);
            dp[i] = 1;
            int t = i;
            while(t != 1) {
                if(dp[t] > max1[fa[t]]) {
                    max2[fa[t]] = max1[fa[t]];
                    max1[fa[t]] = dp[t];
                } else {
                    max2[fa[t]] = max(max2[fa[t]], dp[t]);
                }
                t = fa[t];
                if(max(max1[t], max2[t] + 1) == dp[t]) {
                    break;
                }
                dp[t] = max(max1[t], max2[t] + 1);
            }
            printf("%d%c", max1[1], (i <= n)? ' ': '\n');
        }
    }
    return 0;
}

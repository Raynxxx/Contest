/*
** HDU 1695 GCD
** Created by Rayn @@ 2014/11/04
*/
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long Long;
using namespace std;
const int MAXN = 100010;

Long euler[MAXN];
int factor[MAXN][20];
int factorCnt[MAXN];

void euler_table() {
    euler[1] = 1;
    for(int i = 2; i < MAXN; ++i) {
        if(euler[i] == 0) {
            for(int j = i; j < MAXN; j += i) {
                if(euler[j] == 0) {
                    euler[j] = j;
                }
                euler[j] = euler[j] * (i - 1) / i;
                factor[j][factorCnt[j]++] = i;
            }
        }
    }
    for(int i = 2; i < MAXN; ++i) {
        euler[i] += euler[i - 1];
    }
}
Long dfs(int x, int b, int now) {
    Long ret = 0;
    for(int i = x; i < factorCnt[now]; ++i) {
        ret += b / factor[now][i] - dfs(i + 1, b / factor[now][i], now);
    }
    return ret;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    euler_table();
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        int a, b, c, d, k;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        if(k == 0) {
            printf("Case %d: 0\n", ++cases);
            continue;
        }
        b /= k, d /= k;
        if(d < b) swap(d, b);
        Long ret = euler[b];
        for(int i = b + 1; i <= d; ++i) {
            ret += (Long)b - dfs(0, b, i);
        }
        printf("Case %d: %I64d\n", ++cases, ret);
    }
    return 0;
}

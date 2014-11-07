/*
** CF 438C The Child and Polygon
** Created by Rayn @@ 2014/10/01
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 210;
const long long MOD = 1000000007;

struct Point {
    long long x, y;
    Point() {}
    Point(LL x, LL y): x(x), y(y) {}
    Point operator + (const Point& p) const {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) const {
        return Point(x-p.x, y-p.y);
    }
};

Point vertex[MAXN];
LL dp[MAXN][MAXN];

long long Cross(const Point& A, const Point& B) {
    return A.x*B.y - A.y*B.x;
}

bool IsClockwise(int n) {
    long long ret = 0;
    for(int i = 0; i < n; ++i) {
        ret += Cross(vertex[i], vertex[(i+1)%n]);
    }
    return ret < 0;
}
long long Gao(int l, int r) {
    if(dp[l][r] != -1) {
        return dp[l][r];
    }
    LL& ret = dp[l][r] = 0;
    if(l + 1 == r) {
        return ret = 1;
    }
    for(int k = l + 1; k < r; ++k) {
        if(Cross(vertex[r] - vertex[l], vertex[k] - vertex[l]) > 0) {
            ret = (ret + Gao(l, k) * Gao(k, r)) % MOD;
        }
    }
    return ret;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) {
            long long x, y;
            scanf("%I64d%I64d", &x, &y);
            vertex[i] = Point(x, y);
        }
        if(!IsClockwise(n)) {
            reverse(vertex, vertex + n);
        }
        memset(dp, -1, sizeof(dp));
        printf("%I64d\n", Gao(0, n-1));
    }
    return 0;
}

/*
** CF 485B Valuable Resources
** Created by Rayn @@ 2014/11/07
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 1005;
const int INF = 0x3F3F3F3F;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        int l = INF, r = -INF, t = -INF, b = INF;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            l = min(l, x);
            r = max(r, x);
            t = max(t, y);
            b = min(b, y);
        }
        Long side = max(r - l, t - b);
        printf("%I64d\n", side * side);
    }
    return 0;
}

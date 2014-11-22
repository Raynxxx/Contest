/*
** POJ 3370 Halloween treats
** Created by Rayn @@ 2014/11/03
*/
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 100010;

int nextInt() {
    char ch = getchar();
    bool flag = false;
    while ((ch < '0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while (ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if (flag) ret = -ret;
    return ret;
}

int a[MAXN];
int flag[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int c, n;
    while (scanf("%d%d", &c, &n) != EOF && (c && n)) {
        for (int i = 1; i <= n; ++i) {
            a[i] = nextInt();
        }
        fill_n(flag, c + 1, 0);
        int sum = 0, st, ed;
        for (int i = 1; i <= n; ++i) {
            sum = (sum + a[i]) % c;
            if (sum == 0) {
                st = 1, ed = i;
                break;
            } else if (flag[sum]) {
                st = flag[sum] + 1;
                ed = i;
                break;
            } else {
                flag[sum] = i;
            }
        }
        for (int i = st; i <= ed; ++i) {
            printf("%d%c", i, (i == ed) ? '\n' : ' ');
        }
    }
    return 0;
}

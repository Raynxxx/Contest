/*
** CF 483C Diverse Permutation
** Created by Rayn @@ 2014/11/13
*/
#include <set>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long Long;

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

int a[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF) {
        int pt = 1;
        int u = 1, v = k + 1;
        while (u < v) {
            a[pt++] = u;
            a[pt++] = v;
            u++, v--;
        }
        a[pt++] = u;
        for (int i = k + 2; i <= n; ++i) {
            a[i] = i;
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", a[i], (i == n) ? '\n' : ' ');
        }
    }
    return 0;
}

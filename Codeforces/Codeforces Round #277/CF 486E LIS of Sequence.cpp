/*
** CF 486E LIS of Sequence
** Created by Rayn @@ 2014/11/13
*/
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

int n, a[MAXN];
int vis[MAXN], box[MAXN];
int f1[MAXN], f2[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        int LIS = 0;
        fill_n(box, n + 1, INF);
        for (int i = 1; i <= n; ++i) {
            int k = lower_bound(box + 1, box + 1 + n, a[i]) - box;
            f1[i] = k;
            LIS = max(LIS, k);
            box[k] = a[i];
        }
        fill_n(box, n + 1, INF);
        for (int i = n; i >= 1; --i) {
            int k = lower_bound(box + 1, box + 1 + n, -a[i]) - box;
            box[k] = -a[i];
            f2[i] = k;
        }
        fill_n(vis, n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            //printf("%d : f1 %d -- f2 %d\n", i, f1[i], f2[i]);
            if (f1[i] + f2[i] - 1 == LIS) {
                ++vis[f1[i]];
            }
        }
        string ret = "";
        for (int i = 1; i <= n; ++i) {
            if (f1[i] + f2[i] - 1 < LIS) {
                ret += '1';
            } else if (vis[f1[i]] == 1) {
                ret += '3';
            } else {
                ret += '2';
            }
        }
        printf("%s\n", ret.c_str());
    }
    return 0;
}

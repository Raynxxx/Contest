/*
** CF 479D Long Jumps
** Created by Rayn @@ 2014/11/10
*/
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

const int MAXN = 100000 + 10;
const int INF = 0x3F3F3F3F;

int pt[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, l, x, y;
    while (scanf("%d%d%d%d", &n, &l, &x, &y) != EOF) {
        set<int> box;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &pt[i]);
            box.insert(pt[i]);
        }
        bool fx = false , fy = false;
        for (int i = 1; i <= n; ++i) {
            if (box.count(pt[i] - x)) fx = true;
            if (box.count(pt[i] - y)) fy = true;
        }
        if (fx && fy) {
            puts("0");
        } else if (!fx && fy) {
            puts("1");
            printf("%d\n", x);
        } else if (fx && !fy) {
            puts("1");
            printf("%d\n", y);
        } else {
            bool ok = false;
            for (int i = 1; i <= n; ++i) {
                if (box.count(pt[i] - x - y)) {
                    puts("1");
                    printf("%d\n", pt[i] - x);
                    ok = true;
                    break;
                }
                if (box.count(pt[i] + x - y)) {
                    if (pt[i] + x <= l) {
                        puts("1");
                        printf("%d\n", pt[i] + x);
                        ok = true;
                        break;
                    } else if (pt[i] - y >= 0) {
                        puts("1");
                        printf("%d\n", pt[i] - y);
                        ok = true;
                        break;
                    }
                }
            }
            if (!ok) {
                puts("2");
                printf("%d %d\n", x, y);
            }
        }
    }
    return 0;
}

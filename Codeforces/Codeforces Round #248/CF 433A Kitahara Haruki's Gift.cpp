/*
** CF 433A Kitahara Haruki's Gift
** Created by Rayn @@ 2014/11/14
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
typedef pair<int, int> pii;

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, t1, t2, sum;
    while (scanf("%d", &n) != EOF) {
        t1 = t2 = sum = 0;
        for (int i = 0, w; i < n; ++i) {
            scanf("%d", &w);
            if (w == 100) {
                t1++;
            } else {
                t2++;
            }
            sum += w;
        }
        if (sum % 200 == 0 && ((t1 % 2 == 0 && t2 % 2 == 0) || (t2 % 2 == 1 && t1 >= 2))) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
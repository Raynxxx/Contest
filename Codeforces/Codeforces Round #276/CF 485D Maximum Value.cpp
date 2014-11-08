/*
** CF 485D Maximum Value
** Created by Rayn @@ 2014/11/08
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
const int MAXA = 1000000;
const int MAXN = 2000005;

int near[MAXN];
bool occur[MAXN];

int main() {
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        fill_n(occur, MAXN, false);
        fill_n(near, MAXN, 0);
        for (int i = 0, x; i < n; ++i) {
            scanf("%d", &x);
            occur[x] = true;
        }
        for (int i = 1; i <= MAXA * 2; ++i) {
            near[i] = occur[i - 1] ? i - 1 : near[i - 1];
        }
        int ret = 0;
        for (int i = 2; i <= MAXA; ++i) {
            if (occur[i] == true) {
                for (int j = i * 2; j < MAXA + i; j += i) {
                    if (near[j] > i) {
                        ret = max(ret, near[j] % i);
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}

/*
** CF 485C Bits
** Created by Rayn @@ 2014/11/07
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

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        while (n--) {
            Long l, r;
            scanf("%I64d%I64d", &l, &r);
            for (int i = 0; i < 63; ++i) {
                if ((l | (1LL << i)) <= r) {
                    l |= 1LL << i;
                }
            }
            printf("%I64d\n", l);
        }
    }
    return 0;
}

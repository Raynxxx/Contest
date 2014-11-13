/*
** CF 483A Counterexample
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

Long gcd(Long a, Long b) {
    return (b == 0) ? a : gcd(b, a % b);
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Long l, r;
    while (cin >> l >> r) {
        bool ok = true;
        for (Long a = l; a <= r && ok; ++a) {
            for (Long b = a + 1; b <= r && ok; ++b) {
                for (Long c = b + 1; c <= r && ok; ++c) {
                    if (gcd(a, b) == 1 && gcd(b, c) == 1) {
                        if (gcd(a, c) != 1) {
                            printf("%I64d %I64d %I64d\n", a, b, c);
                            ok = false;
                            break;
                        }
                    }
                }
            }
        }
        if (ok) {
            puts("-1");
        }
    }
    return 0;
}

/*
** CF 483B Friends and Presents
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

Long cnt1, cnt2, x, y;

bool Check(Long v) {
    Long f1 = v / x;
    Long f2 = v / y;
    Long both = v / (x * y);
    Long other = v - f1 - f2 + both;
    Long ff1 = f1 - both;
    Long ff2 = f2 - both;
    Long g1 = max(0LL, cnt1 - ff2);
    Long g2 = max(0LL, cnt2 - ff1);
    return g1 + g2 <= other;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    while (cin >> cnt1 >> cnt2 >> x >> y) {
        Long l = 0, r = (Long)1e18;
        while (l < r) {
            Long mid = (l + r) >> 1;
            if (Check(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << l << endl;
    }
    return 0;
}       
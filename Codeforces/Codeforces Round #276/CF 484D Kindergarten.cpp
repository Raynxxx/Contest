/*
** CF 484D Kindergarten
** Created by Rayn @@ 2014/11/10
*/
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int MAXN = 1000005;

int a[MAXN];
Long dp[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        int pos = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = max(dp[pos - 1] + abs(a[i] - a[pos]), dp[pos] + abs(a[i] - a[pos + 1]));
            if (a[i - 1] <= a[i] && a[i] >= a[i + 1]) {
                pos = i;
            }
            if (a[i - 1] >= a[i] && a[i] <= a[i + 1]) {
                pos = i;
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}

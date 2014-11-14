/*
** CF 433B Kuriyama Mirai's Stones
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

int stone[MAXN], sorted[MAXN];
Long f[2][MAXN];

void Build(int n) {
    f[0][0] = f[1][0] = 0;
    for (int i = 1; i <= n; ++i) {
        f[0][i] = f[0][i - 1] + stone[i];
        f[1][i] = f[1][i - 1] + sorted[i];
    }
}
Long Query(int idx, int l, int r) {
    return f[idx][r] - f[idx][l - 1];
}

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    int n, m;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            cin >> stone[i];
            sorted[i] = stone[i];
        }
        sort(sorted + 1, sorted + 1 + n);
        Build(n);
        cin >> m;
        while (m--) {
            int type, l, r;
            cin >> type >> l >> r;
            if (type == 1) {
                cout << Query(0, l, r) << endl;
            } else {
                cout << Query(1, l, r) << endl;
            }
        }
    }
    return 0;
}
/*
** UVA 106 Fermat vs. Pythagoras
** Created by Rayn on 2014/12/12
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 1000000 + 10;

bool tag[MAXN];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}
int sqr(int x) {
    return x * x;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n) {
        fill_n(tag, n + 1, false);
        int bounds = (int) sqrt(n + 0.5);
        int total = 0, unused = 0;
        for (int i = 1; i <= bounds; ++i) {
            for (int j = i + 1; j <= bounds; j += 2) {
                if (gcd(i, j) == 1 && sqr(i) + sqr(j) <= n) {
                    total++;
                    int x = sqr(j) - sqr(i);
                    int y = 2 * i * j;
                    int z = sqr(j) + sqr(i);
                    for (int k = 1; k * z <= n; ++k) {
                        tag[k * x] = true;
                        tag[k * y] = true;
                        tag[k * z] = true;
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (!tag[i]) {
                unused++;
            }
        }
        cout << total << " " << unused << endl;
    }
    return 0;
}
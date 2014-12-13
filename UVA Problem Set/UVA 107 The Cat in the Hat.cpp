/*
** UVA 107 The Cat in the Hat
** Created by Rayn on 2014/12/13
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
const double EPS = 1e-8;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int height, workers;
    while (cin >> height >> workers && (height || workers)) {
        int step;
        for (int k = 0; k < 64; ++k) {
            double h = pow(pow(workers, 1.0 / k) + 1.0, k * 1.0);
            if (fabs(h - height) < EPS) {
                step = k;
                break;
            }
        }
        int n = int(pow(workers, 1.0 / step) + EPS);
        int cnt = 0, sum = workers;
        int tmp = height;
        for (int i = 0; i < step; ++i) {
            int cur = int(pow(n * 1.0, i) + EPS);
            cnt += cur;
            sum += int(cur * tmp + EPS);
            tmp = int(ceil(tmp * 1.0 / (n + 1)));
        }
        cout << cnt << " " << sum << endl;
    }
    return 0;
}
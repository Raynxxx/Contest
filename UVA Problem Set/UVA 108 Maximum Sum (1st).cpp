/*
** UVA 108 Maximum Sum (1st)
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

const int MAXN = 100 + 10;
const int INF = 0x3F3F3F3F; 

int matrix[MAXN][MAXN];
int sum[MAXN][MAXN];

int getSum(int i, int j, int w, int h) {
    return sum[i + w - 1][j + h - 1] - sum[i + w - 1][j - 1] - sum[i - 1][j + h - 1] + sum[i - 1][j - 1];
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> matrix[i][j];
            }
        }
        for (int i = 0; i <= n; ++i) {
            sum[0][i] = sum[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i][j];
                //cout << sum[i][j] << " ";
            }
            //cout << endl;
        }
        int ret = -INF;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int x = 1; i + x - 1 <= n; ++x) {
                    for (int y = 1; j + y - 1 <= n; ++y) {
                        ret = max(ret, getSum(i, j, x, y));
                    }
                }
            }
        }
        cout << ret << endl;
    }
    return 0;
}
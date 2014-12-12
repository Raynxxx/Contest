/*
** UVA 104 Arbitrage
** Created by Rayn on 2014/12/12
*/
#include <stack>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXD = 20 + 5;
const double EPS = 1e-4;

double rate[MAXD][MAXD][MAXD];
int pre[MAXD][MAXD][MAXD];

void gao(int n, int &res, int &start) {
    res = start = 1;
    for (int step = 2; step <= n; ++step) {
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (rate[i][k][step - 1] * rate[k][j][1] > rate[i][j][step] + EPS) {
                        rate[i][j][step] = rate[i][k][step - 1] * rate[k][j][1];
                        pre[i][j][step] = k;
                    }
                    if (i == j && rate[i][j][step] > 1.01 + EPS) {
                        res = step;
                        start = i;
                        return;
                    }
                }
            }
        }
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        memset(rate, 0, sizeof(rate));
        memset(pre, 0, sizeof(pre));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j) {
                    cin >> rate[i][j][1];
                } else {
                    rate[i][j][1] = 1.0;
                }
                pre[i][j][1] = i;
            }
        }
        int step, start;
        gao(n, step, start);
        if (step == 1) {
            cout << "no arbitrage sequence exists" << endl;
        } else {
            vector<int> path;
            int s = step, last = start;
            while (s >= 0) {
                path.push_back(last);
                last = pre[start][last][s--];
            }
            reverse(path.begin(), path.end());
            for (int i = 0; i < step + 1; ++i) {
                cout << path[i] << (i == step ? '\n' : ' ');
            }
        }
    }
    return 0;
}
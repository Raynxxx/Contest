/*
** UVA 100 The 3n + 1 problem
** Created by Rayn on 2014/12/10
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int gao(int n) {
    int ret = 1;
    while (n != 1) {
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        ret++;
    }
    return ret;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int first, last;
    while (cin >> first >> last) {
        int n = min(first, last);
        int m = max(first, last);
        int cycle = 0;
        for (int i = n; i <= m; ++i) {
            cycle = max(cycle, gao(i));
        }
        cout << first << " " << last << " " << cycle << endl;
    }
    return 0;
}

/*
** CF 443B Kolya and Tandem Repeat
** Created by Rayn @@ 2014/11/24
*/
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    string str;
    int k, n;
    while (cin >> str >> k) {
        n = str.length();
        if (k >= n) {
            cout << ((n + k) / 2) * 2 << endl;
        } else {
            int ret = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = ret + 1; i + 2 * j <= n + k; ++j) {
                    bool ok = true;
                    for (int m = 0; m < j && i + j + m < n && ok; ++m) {
                        if (str[i + m] != str[i + j + m]) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        ret = j;
                    }
                }
            }
            cout << ret * 2 << endl;
        }
    }
    return 0;
}

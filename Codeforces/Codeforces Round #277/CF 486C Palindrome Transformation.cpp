/*
** CF 486C Palindrome Transformation
** Created by Rayn @@ 2014/11/12
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100010;

string str;
bool flag[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, p;
    while (cin >> n >> p) {
        cin >> str;
        str = '#' + str;
        fill_n(flag, n + 1, false);
        int ret = 0;
        for (int i = 1; i <= n / 2; ++i) {
            if (str[i] != str[n - i + 1]) {
                if (abs(p - i) > abs(p - (n - i + 1))) {
                    flag[n - i + 1] = true;
                } else {
                    flag[i] = true;
                }
                int diff = abs(str[i] - str[n - i + 1]);
                ret += min(diff, 26 - diff);
            }
        }
        int L = p, R = p;
        for (int i = 1; i < p; ++i) {
            if (flag[i]) {
                L = i;
                break;
            }
        }
        for (int i = n; i > p; --i) {
            if (flag[i]) {
                R = i;
                break;
            }
        }
        ret += abs(p - L) + abs(p - R) + min(abs(p - L), abs(p - R));
        cout << ret << endl;
    }
    return 0;
}
 
/*
** CF 443A Anton and Letters
** Created by Rayn @@ 2014/11/24
*/
#include <set>
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

    string buf;
    while (getline(cin, buf)) {
        int len = buf.length();
        set<char> writing;
        for (int i = 1; i < len - 1; ++i) {
            if ('a' <= buf[i] && buf[i] <= 'z') {
                writing.insert(buf[i]);
            }
        }
        cout << writing.size() << endl;
    }
    return 0;
}

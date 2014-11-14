/*
** CF 437A The Child and Homework
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



int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    string choice[4];
    int len[4];
    for (int i = 0; i < 4; ++i) {
        cin >> choice[i];
        len[i] = choice[i].length() - 2;
    }
    vector<int> good;
    for (int i = 0; i < 4; ++i) {
        bool f1 = true, f2 = true;
        for (int j = 0; j < 4; ++j) {
            if (j == i) continue;
            f1 = f1 & (len[i] * 2 <= len[j]);
            f2 = f2 & (len[j] * 2 <= len[i]);
        }
        if (f1 || f2) good.push_back(i);
    }
    if (good.size() != 1) {
        puts("C");
    } else {
        printf("%c\n", char('A' + good[0]));
    }
    return 0;
}
/*
** CF 485A Factory
** Created by Rayn @@ 2014/11/07
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100005;

bool occur[MAXN];

int main() {
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int a, m;
    while (scanf("%d%d", &a, &m) != EOF) {
        fill_n(occur, m + 1, false);
        bool stop = false;
        while (true) {
            if (a % m == 0) {
                stop = true;
                break;
            } else if (occur[a % m]) {
                stop = false;
                break;
            }
            occur[a % m] = true;
            a = (a + a % m) % m;
        }
        if (stop) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}

/*
** CF 479B Towers
** Created by Rayn @@ 2014/11/10
*/
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef pair<int, int> pii;
typedef vector<pii>::iterator Iter;
typedef long long Long;

const int MAXN = 110;

int height[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, k, x;
    while (scanf("%d%d", &n, &k) != EOF) {
        vector<pii> box;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            box.push_back(make_pair(x, i));
        }
        vector<pii> step;
        while (k--) {
            sort(box.begin(), box.end());
            //printf("%d %d\n", box.back().first, box.front().first);
            int diff = box.back().first - box.front().first;
            if (diff <= 1) {
                break;
            }
            step.push_back(make_pair(box.back().second, box.front().second));
            --box.back().first;
            ++box.front().first;
        }
        sort(box.begin(), box.end());
        printf("%d %d\n", box.back().first - box.front().first, step.size());
        for (Iter it = step.begin(); it != step.end(); ++it) {
            printf("%d %d\n", it->first, it->second);
        }
    }
    return 0;
}

/*
** CF 437B The Child and Set
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

const int MAXN = 100005;
int LowBit(int x) {
    return x & (-x);
}

pii box[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    int sum, limit;
    while (cin >> sum >> limit) {
        for (int i = 1; i <= limit; ++i) {
            box[i] = make_pair(LowBit(i), i);
        }
        sort(box + 1, box + 1 + limit, greater<pii>());
        vector<int> ret;
        for (int i = 1; i <= limit && sum > 0; ++i) {
            if (box[i].first <= sum) {
                sum -= box[i].first;
                ret.push_back(box[i].second);
            }
        }
        if (sum > 0) {
            puts("-1");
        } else {
            int sz = ret.size();
            cout << sz << endl;
            for (int i = 0; i < sz; ++i) {
                cout << ret[i] << (i == sz - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
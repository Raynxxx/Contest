/*
** UVA 103 Stacking Boxes
** Created by Rayn on 2014/12/11
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAX_BOX = 30 + 5;
const int MAX_D = 10 + 5;

struct BoxNode {
    int id, n;
    int d[MAX_D];

    void Init(int id, int n) {
        this->id = id;
        this->n = n;
    }
    void rearranged() {
        sort(d, d + n);
    }
    friend bool operator < (const BoxNode& A, const BoxNode& B) {
        for (int i = 0; i < A.n; ++i) {
            if (A.d[i] > B.d[i]) {
                return false;
            }
        }
        return true;
    }
};


BoxNode box[MAX_BOX];
bool link[MAX_BOX][MAX_BOX];
int dp[MAX_BOX];
int pre[MAX_BOX];

bool isLess(int n, int x, int y) {
    for (int i = 0; i < n; ++i) {
        if (box[x].d[i] >= box[y].d[i]) {
            return false;
        }
    }
    return true;
}
void getOrder(int last, vector<int>& order) {
    order.push_back(box[last].id);
    if (pre[last] != -1) {
        getOrder(pre[last], order);
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    int k, n;
    while (cin >> k >> n) {
        for (int i = 0; i < k; ++i) {
            box[i].Init(i + 1, n);
            for (int j = 0; j < n; ++j) {
                cin >> box[i].d[j];
            }
            box[i].rearranged();
        }
        sort(box, box + k);
        memset(link, false, sizeof(link));
        for (int i = 0; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                if (isLess(n, i, j)) {
                    link[i][j] = true;
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            dp[i] = 1;
            pre[i] = -1;
        }
        int longest = 1, last = 0;
        for (int ed = 1; ed < k; ++ed) {
            for (int st = 0; st < ed; ++st) {
                if (link[st][ed] && dp[ed] < dp[st] + 1) {
                    dp[ed] = dp[st] + 1;
                    pre[ed] = st;
                }
            }
            if (dp[ed] > longest) {
                longest = dp[ed];
                last = ed;
            }
        }
        vector<int> order;
        getOrder(last, order);
        reverse(order.begin(), order.end());
        cout << longest << endl;
        for (int i = 0; i < longest; ++i) {
            cout << order[i] << (i == longest - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

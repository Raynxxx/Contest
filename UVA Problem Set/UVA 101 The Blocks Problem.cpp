/*
** UVA 101 The Blocks Problem
** Created by Rayn on 2014/12/10
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

vector<int> table[25];

void Init_table(int n) {
    for (int i = 0; i < n; ++i) {
        table[i].clear();
        table[i].push_back(i);
    }
}
pii find_block(int n, int idx) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int) table[i].size(); ++j) {
            if (table[i][j] == idx) {
                return make_pair(i, j);
            }
        }
    }
}
void Back(pii pos) {
    int idx = pos.first, height = pos.second;
    for (int y = height + 1; y < (int) table[idx].size(); ++y) {
        int orgin = table[idx][y];
        table[orgin].push_back(orgin);
    }
    table[idx].resize(height + 1);
}
void Put(pii pa, pii pb) {
    int idx = pa.first, height = pa.second;
    for (int i = height; i < (int) table[idx].size(); ++i) {
        table[pb.first].push_back(table[idx][i]);
    }
    table[idx].resize(height);
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b;
    string cmd, op;
    while (cin >> n) {
        Init_table(n);
        while (cin >> cmd && cmd != "quit") {
            cin >> a >> op >> b;
            pii pa = find_block(n, a);
            pii pb = find_block(n, b);
            if (pa.first == pb.first) {
                continue;
            }
            if (cmd == "move") {
                if (op == "onto") {
                    Back(pa);
                    Back(pb);
                } else {
                    Back(pa);
                }
            } else {
                if (op == "onto") {
                    Back(pb);
                }
            }
            Put(pa, pb);
        }
        for (int i = 0; i < n; ++i) {
            cout << i << ":";
            for (int j = 0; j < (int) table[i].size(); ++j) {
                cout << " " << table[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}

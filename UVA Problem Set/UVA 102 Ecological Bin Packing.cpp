/*
** UVA 102 Ecological Bin Packing
** Created by Rayn on 2014/12/10
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const Long INF = 1LL << 60;
const char color[] = { 'B', 'C', 'G' };

int bins[3][3];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);

    while (cin >> bins[0][0] >> bins[0][2] >> bins[0][1] >> 
        bins[1][0] >> bins[1][2] >> bins[1][1] >> 
        bins[2][0] >> bins[2][2] >> bins[2][1]) {
        string order = "012", idea = "";
        Long ret = INF;
        do {
            Long swap_time = 0;
            for (int i = 0; i < 3; ++i) {
                int cur = order[i] - '0';
                for (int j = 0; j < 3; ++j) {
                    if (i == j) continue;
                    swap_time += bins[j][cur];
                }
            }
            if (swap_time < ret) {
                ret = swap_time;
                idea = order;
            }
        } while (next_permutation(order.begin(), order.end()));
        for (int i = 0; i < 3; ++i) {
            idea[i] = color[idea[i] - '0'];
        }
        cout << idea << " " << ret << endl;
    }
    return 0;
}

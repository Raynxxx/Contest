/*
** CF 479C Exams
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
typedef long long Long;

const int MAXN = 5000 + 10;
const int INF = 0x3F3F3F3F;

struct Item {
    int a, b;
    void read() {
        scanf("%d%d", &a, &b);
    }
    bool operator < (const Item& rhs) const {
        return a < rhs.a || (a == rhs.a && b < rhs.b);
    }
};

Item exam[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            exam[i].read();
        }
        sort(exam, exam + n);
        int day = 0;
        for (int i = 0; i < n; ++i) {
            if (exam[i].b >= day) {
                day = exam[i].b;
            } else if (exam[i].b < day) {
                day = exam[i].a;
            }
        }
        printf("%d\n", day);
    }
    return 0;
}
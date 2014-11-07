/*
** HDU 5095 Linearization of the kernel functions in SVM
** Created by Rayn @@ 2014/11/02
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long Long;
const int MAXN = 10010;
const char op[] = { "pqruvwxyz" };
int data[15];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 10; ++i) {
            scanf("%d", &data[i]);
        }
        bool first = true;
        for (int i = 0; i < 9; ++i) {
            if (data[i]) {
                if (!first && data[i] > 0) {
                    printf("+");
                }
                if (data[i] == -1) {
                    printf("-");
                } else if (data[i] != 1) {
                    printf("%d", data[i]);
                }
                putchar(op[i]);
                first = false;
            }
        }
        if (data[9]) {
            if (!first && data[9] > 0)
                printf("+");
            printf("%d", data[9]);
            first = false;
        }
        if (first) {
            printf("0");
        }
        printf("\n");
    }
    return 0;
}

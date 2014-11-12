/*
** CF 486B OR in Matrix
** Created by Rayn @@ 2014/11/12
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 105;

int m, n;
int A[MAXN][MAXN];
int B[MAXN][MAXN];

void Assign(int r, int c) {
    for (int k = 1; k <= n; ++k) {
        A[r][k] = 0;
    }
    for (int t = 1; t <= m; ++t) {
        A[t][c] = 0;
    }
}
int Generate(int r, int c) {
    int ret = 0;
    for (int k = 1; k <= n; ++k) {
        ret |= A[r][k];
    }
    for (int t = 1; t <= m; ++t) {
        ret |= A[t][c];
    }
    return ret;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while (scanf("%d%d", &m, &n) != EOF) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &B[i][j]);
                A[i][j] = 1;
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (B[i][j] == 0) {
                    Assign(i, j);
                }
            }
        }
        bool can = true;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (Generate(i, j) != B[i][j]) {
                    can = false;
                    break;
                }
            }
        }
        if (can) {
            puts("YES");
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    printf("%d%c", A[i][j], (j == n) ? '\n' : ' ');
                }
            }
        } else {
            puts("NO");
        }
    }
    return 0;
}
 
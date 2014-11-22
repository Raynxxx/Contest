/*
** POJ 3744 Scout YYF I
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int INF = 1 << 27;

struct Matrix
{
    int n, m;
    vector< vector<double> > a;

    Matrix() {}
    Matrix(int n, int m): n(n), m(m) {
        a.resize(n);
        for(int i = 0; i < n; ++i) {
            a[i].resize(m, 0);
        }
    }
    friend Matrix operator * (const Matrix& A, const Matrix& B) {
        Matrix ret(A.n, B.m);
        for(int i = 0; i < A.n; ++i) {
            for(int j = 0; j < B.m; ++j) {
                for(int k = 0; k < A.m; ++k) {
                    ret.a[i][j] += A.a[i][k] * B.a[k][j];
                }
            }
        }
        return ret;
    }
};

Matrix QuickPow(Matrix a, int n)
{
    int k = min(a.n, a.m);
    Matrix ret(k, k);
    for(int i = 0; i < k; ++i) {
        ret.a[i][i] = 1;
    }
    while(n) {
        if(n & 1) ret = ret * a;
        a = a * a;
        n >>= 1;
    }
    return ret;
}

int mine[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    double p;
    while(scanf("%d%lf", &n, &p) != EOF)
    {
        mine[0] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &mine[i]);
        }
        sort(mine, mine + n + 1);
        Matrix m(2, 2), dp;
        m.a[0][0] = p, m.a[0][1] = 1 - p;
        m.a[1][0] = 1, m.a[1][1] = 0;
        double ret = 1.0;
        for(int i = 1; i <= n; ++i) {
            if(mine[i] == mine[i-1])
                continue;
            dp = QuickPow(m, mine[i]-mine[i-1]-1);
            ret *= (1 - dp.a[0][0]);
        }
        printf("%.7f\n", ret);
    }
    return 0;
}

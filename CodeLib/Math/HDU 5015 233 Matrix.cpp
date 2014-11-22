/*
** HDU 5015 233 Matrix
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 15;
const int MOD = 10000007;

template <typename T>
struct Matrix
{
    int n, m;
    vector< vector<T> > a;

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
                    ret.a[i][j] = (ret.a[i][j] + (LL)A.a[i][k] * B.a[k][j]) % MOD;
                }
            }
        }
        return ret;
    }
    friend Matrix operator ^ (Matrix& A, int& n) {
        int k = min(A.n, A.m);
        Matrix ret(k, k);
        for(int i = 0; i < k; ++i) ret.a[i][i] = 1;
        while(n) {
            if(n & 1)
                ret = ret * A;
            A = A * A;
            n >>= 1;
        }
        return ret;
    }
    void OutPut() {
        cout << "****************" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << "****************" << endl;
    }
};

int col[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(int i = n-1; i >= 0; --i) {
            scanf("%d", &col[i]);
        }
        col[n] = 233;
        col[n+1] = 3;
        Matrix<int> A(n+2, n+2);
        for(int i = 0; i < n + 2; ++i) {
            for(int j = i; j < n + 2; ++j) {
                A.a[i][j] = 1;
            }
        }
        for(int i = 0; i < n; ++i) A.a[i][n+1] = 0;
        A.a[n][n] = 10;
        Matrix<int> B = A ^ m;
        int res = 0;
        for(int i = 0; i < n + 2; ++i) {
            res = (res + (LL)B.a[0][i] * col[i]) % MOD;
        }
        printf("%d\n", res);
    }
    return 0;
}

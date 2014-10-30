/*
** HDU 4965 Fast Matrix Calculation
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int MOD = 6;
const int MAXN = 1010;
const int MAXK = 10;

int N, K;

template <typename T> void fastRead(T& ret)
{
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

struct Matrix
{
    int n, m;
    vector< vector<int> > a;

    Matrix() {}
    Matrix(int n, int m): n(n), m(m)
    {
        a.resize(n);
        for(int i = 0; i < n; ++i) {
            a[i].resize(m, 0);
        }
    }
    void setIdentity(int k)
    {
        for(int i = 0; i < k; ++i) {
            a[i][i] = 1;
        }
    }
    friend Matrix operator * (const Matrix& A, const Matrix& B)
    {
        Matrix ret(A.n, B.m);
        for(int i = 0; i < A.n; ++i) {
            for(int j = 0; j < B.m; ++j) {
                for(int k = 0; k < A.m; ++k) {
                    ret.a[i][j] += A.a[i][k] * B.a[k][j];
                }
                ret.a[i][j] %= MOD;
            }
        }
        return ret;
    }
};

void QuickPowMod(Matrix& x, int n)
{
    Matrix ret(K, K);
    ret.setIdentity(K);
    while(n)
    {
        if(n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    x = ret;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &N, &K) != EOF)
    {
        if(N == 0 && K == 0)
            break;
        Matrix A(N, K), B(K, N);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < K; ++j) {
                //scanf("%d", &A.a[i][j]);
                fastRead(A.a[i][j]);
            }
        }
        for(int i = 0; i < K; ++i) {
            for(int j = 0; j < N; ++j) {
                //scanf("%d", &B.a[i][j]);
                fastRead(B.a[i][j]);
            }
        }
        Matrix C = B * A;
        QuickPowMod(C, N*N-1);
        Matrix M = (A * C) * B;
        int sum = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                sum += M.a[i][j];
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}

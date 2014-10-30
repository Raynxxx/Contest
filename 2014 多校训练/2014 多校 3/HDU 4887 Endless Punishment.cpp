/*
** HDU 4887 Endless Punishment
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int D = 33;
const int MOD = 2;

int n, S1, S2;
int s1[D], s2[D];
int Start[D], End[D];
map<LL, int> Hash;

struct Matrix
{
    int a[D][D];

    Matrix() {
        memset(a, 0, sizeof(a));
    }
    Matrix operator * (const Matrix& b) const {
        Matrix ret;
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= n; ++j) {
                ret.a[i][j] = 0;
                for(int k = 0; k <= n; ++k) {
                    ret.a[i][j] += a[i][k] * b.a[k][j];
                }
                ret.a[i][j] %= MOD;
            }
        }
        return ret;
    }
    void setIdentity(int n) {
        for(int i = 0; i <= n; ++i) {
            a[i][i] = 1;
        }
    }
    void showMartix(int D) {
        puts("");
        for(int i = 0; i < D; ++i) {
            for(int j = 0; j < D; ++j) {
                printf("%d ", a[i][j]);
            }
            puts("");
        }
        puts("");
    }
};

bool input()
{
    if(scanf("%d%d%d", &n, &S1, &S2) == EOF) return false;
    for(int i = 0; i < S1; ++i) scanf("%d", &s1[i]);
    for(int i = 0; i < S2; ++i) scanf("%d", &s2[i]);
    for(int i = 0; i < n; ++i)  scanf("%d", &Start[i]);
    for(int i = 0; i < n; ++i)  scanf("%d", &End[i]);
    return true;
}

Matrix QuickPow(Matrix& x, LL times)
{
    Matrix ret;
    ret.setIdentity(n);
    while(times)
    {
        if(times & 1)
            ret = ret * x;
        x = x * x;
        times >>= 1;
    }
    return ret;
}
Matrix getX()
{
    Matrix x;
    x.a[n][n] = 1;
    for(int i = 0; i < S1; ++i) {
        x.a[s1[i]-1][n-1] = 1;
    }
    for(int i = 0; i < n-1; ++i) {
        x.a[i+1][i] = 1;
    }
    for(int i = 0; i < S2; ++i) {
        x.a[n][s2[i]-1] = 1;
    }
    return x;
}

// 只有第一行有效，O（n^2）矩阵乘法
void Mul(Matrix& A, Matrix& B)
{
    int c[D];
    for(int i = 0; i <= n; i++) {
        c[i] = 0;
        for(int j = 0; j <= n; j++) {
            c[i] += A.a[0][j] * B.a[j][i];
        }
        c[i] %= MOD;
    }
    for(int i = 0; i <= n; i++) {
        A.a[0][i] = c[i];
    }
}

LL Solve()
{
    bool flag = true;
    for(int i = 0; i < n; ++i) {
        if(Start[i] != End[i]) {
            flag = false;
            break;
        }
    }
    if(flag) return 0;

    LL tot = 1LL << n;
    int m = (int)sqrt((double)tot) + 1;
    Hash.clear();
    Matrix x = getX();
    Matrix a1, a2;
    for(int i = 0; i < n; i++)  a1.a[0][i] = Start[i];
    for(int i = 0; i < n; i++)  a2.a[0][i] = End[i];
    a1.a[0][n] = a2.a[0][n] = 1;
    //将a2 * x^i的状态放入map中
    for(int i = 0; i < m; ++i) {
        if(i > 0) {
            Mul(a2, x);
        }
        int zt = 0;
        for(int j = 0; j < n; ++j) {
            zt = zt * 2 + a2.a[0][j];
        }
        Hash[zt] = i;
    }
    Matrix tmp = QuickPow(x, m);    //预处理出x^m
    for(int i = 1; i <= m; ++i) {
        Mul(a1, tmp);
        int zt = 0;
        for(int j = 0; j < n; ++j) {
            zt = zt * 2 + a1.a[0][j];
        }
        if(Hash.count(zt)) {
            return (LL)i*m - Hash[zt];
        }
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(input())
    {
        LL res = Solve();
        if(res == -1)
            puts("poor sisyphus");
        else
            printf("%I64d\n", res);
    }
    return 0;
}

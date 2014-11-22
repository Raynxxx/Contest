/*
** ZOJ 3690 Choosing number
** Created by Rayn @@ 2014/07/16
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;

void MartixMul(int a[2][2], int b[2][2], int c[2][2])
{
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            LL tmp = 0;
            for(int k = 0; k < 2; ++k)
            {
                tmp += (LL)a[i][k] * b[k][j];
            }
            c[i][j] = tmp % MOD;
        }
    }
}
void QuickPow(int a[2][2], int n)
{
    if(n == 1)
        return ;
    int b[2][2], r[2][2];
    memcpy(b, a, sizeof(b));
    QuickPow(b, n/2);
    if(n&1)
    {
        MartixMul(b, a, r);
        MartixMul(b, r, a);
    }
    else
    {
        MartixMul(b, b, a);
    }
}
int main() {

#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int n, m, k;
    while(scanf("%d%d%d", &n, &m, &k) != EOF)
    {
        int base[2][2] = {
            {k-1, k  },
            {m-k, m-k}
        };

        QuickPow(base, n);
        int ans = (base[0][1] + base[1][1]) % MOD;
        printf("%d\n", ans);
    }
    return 0;
}

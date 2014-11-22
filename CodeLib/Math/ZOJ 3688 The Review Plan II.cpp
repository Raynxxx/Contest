/*
** ZOJ 3688 The Review Plan II
** Created by Rayn @@ 2014/07/15
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MOD = 1000000007;

int a[100005];
int r[100005];

void Init()
{
    a[1] = a[2] = 0;
    r[1] = a[3] = 1;
    for(int i = 4; i < 100005; i++)
    {
        int x = i-2;
        r[x] = r[MOD%x] * (LL)(MOD - MOD/x) % MOD;
        int aa = (i - 2ll) * i % MOD * a[i-1] % MOD;
        int bb = (a[i-2] * (LL)i + ((i&1)? 4 : MOD-4)) % MOD;
        a[i] = ((LL)aa + bb) * r[x] % MOD;
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int n;
    while(scanf("%d", &n) != EOF)
    {
        printf("%d\n", a[n]);
    }
}

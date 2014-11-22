/*
** LA 6469 Deranged Exams
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

LL C[25][25];
LL fac[25];

void Init()
{
    fac[0] = fac[1] = 1;
    C[1][0] = C[1][1] = 1;
    for(int i = 2; i <= 20; ++i)
    {
        fac[i] = fac[i-1] * (LL)i;
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; ++j)
        {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    Init();

    int T;
    scanf("%d", &T);
    while(T--)
    {
        int cases, n, k;
        scanf("%d%d%d", &cases, &n, &k);
        LL res = fac[n];
        for(int i = 1; i <= k; ++i)
        {
            if(i&1)
                res -= C[k][i] * fac[n-i];
            else
                res += C[k][i] * fac[n-i];
        }
        printf("%d %lld\n", cases, res);
    }
    return 0;
}

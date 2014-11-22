/*
** ZOJ 3648 Gao the Grid II
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
typedef long long LL;
using namespace std;

bool Check(int i, int j, int k, int h)
{
    int a = i*i + k*k;
    int b = h*h + j*j;
    int c = (j-k) * (j-k) + (i-h) * (i-h);
    if(a + b <= c || a + c <= b || b + c <= a)
        return false;
    return true;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        LL ans = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                LL ret = 0;
                for(int k = 1; k <= j-1; ++k)
                {
                    for(int h = 1; h <= i-1; ++h)
                    {
                        if(Check(i, j, k, h))
                            ret += 4;
                    }
                }
                for(int k = 1; k <= j-1; ++k)
                {
                    if(Check(i, j, k, 0))
                        ret += 2;
                }

                for(int h = 1; h <= i-1; ++h)
                {
                    if(Check(i, j, 0, h))
                        ret += 2;
                }
                ans += ret * (n-i+1) * (m-j+1);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

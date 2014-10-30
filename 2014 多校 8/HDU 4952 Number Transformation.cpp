/*
** HDU 4952 Number Transformation
** Created by Rayn @@ 2014/08/25
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;

LL x, k;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%I64d%I64d", &x, &k) != EOF && x+k)
    {
        LL ret = x;
        for(LL i = 2; i <= k; i++)
        {
            ret = ret - ret/i;
            if(ret < i)
                break;
        }
        printf("Case #%d: %I64d\n", ++cases, ret * k);
    }
    return 0;
}

/*
** HDU 4937 Lucky Number
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, cases = 0;
    LL n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%I64d", &n);
        printf("Case #%d: ", ++cases);
        if(n >= 3 && n <= 6)
        {
            printf("-1\n");
            continue;
        }
        LL ans = 0;
        for(LL i = 3; i <= 6; ++i)
        {
            for(LL j = 3; j <= 6; ++j)
            {
                if((n - i)%j == 0 && (n - i)/j > max(i, j)) {
                    ans++;
                }
            }
        }
        for(LL i = 3; i <= 6; ++i)
        {
            for(LL j = 3; j <= 6; ++j)
            {
                for(LL k = 3; k <= 6; ++k)
                {
                    LL a = i, b = j, c = k-n;
                    LL delta = (LL)sqrt(b*b - 4*a*c + 0.5);
                    if(delta*delta != (b*b - 4*a*c))
                        continue;
                    if((delta-b) % (2*a) > 0)
                        continue;
                    if((delta-b) / (2*a) > max(max(i, j), k))
                        ans++;
                }
            }
        }
        for(LL i = 4; i*i*i <= n; ++i)
        {
            LL t = n;
            while(t)
            {
                if(t%i < 3 || t%i > 6)
                    break;
                t /= i;
            }
            if(t == 0)
                ans++;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

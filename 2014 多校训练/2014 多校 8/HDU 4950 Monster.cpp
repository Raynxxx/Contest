/*
** HDU 4950 Monster
** Created by Rayn @@ 2014/08/25
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;
typedef long long LL;

LL h, a, b, k;

int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%I64d%I64d%I64d%I64d",&h,&a,&b,&k) != EOF && h+a+b+k)
    {
        printf("Case #%d: ", ++cases);
        if (a >= h || (a-b)*(k-1) + a >= h || (a-b)*k > b)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

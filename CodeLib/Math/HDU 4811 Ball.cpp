/*
** HDU 4811 Ball
** Created by Rayn @@ 2014/09/26
*/
#include <map>
#include <set>
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

LL Gao(LL x) {
    return (x <= 2)? x : 2;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    LL R, Y, B;
    while(scanf("%I64d%I64d%I64d", &R, &Y, &B) != EOF)
    {
        LL n = R + Y + B;
        LL high = Gao(R) + Gao(Y) + Gao(B);
        LL ret = 0;
        for(LL i = 0; i < n && i < high; ++i) {
            ret += i;
        }
        if(n > high) {
            ret += high * (n - high);
        }
        printf("%I64d\n", ret);
    }
    return 0;
}

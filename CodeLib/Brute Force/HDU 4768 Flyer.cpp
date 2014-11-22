/*
** HDU 4768 Flyer
** Created by Rayn @@ 2014/09/12
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 20010;
const LL INF = 1LL << 32;

int n;
LL A[MAXN], B[MAXN], C[MAXN];

LL Count(LL mid)
{
    LL ret = 0LL;
    for(int i = 0; i < n; ++i) {
        LL up = min(mid, B[i]);
        if(mid >= A[i]) {
            ret += (up - A[i]) / C[i] + 1;
        }
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%I64d %I64d %I64d", &A[i], &B[i], &C[i]);
        }
        LL L = 0, R = INF;
        while(L < R) {
            LL mid = (L + R) >> 1;
            if(Count(mid) % 2) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
        if(L == INF) {
            printf("DC Qiang is unhappy.\n");
            continue;
        }
        while(Count(L) % 2 == 0) L--;
        printf("%I64d %I64d\n", L, Count(L) - Count(L-1));
    }
    return 0;
}

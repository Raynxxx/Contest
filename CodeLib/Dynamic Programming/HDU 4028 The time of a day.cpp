/*
** HDU 4028 The time of a day
** Created by Rayn @@ 2014/09/06
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
typedef map<LL, LL> LLMAP;
typedef LLMAP::iterator MAP_IT;

LL gcd(LL a, LL b)
{
    return b? gcd(b, a%b) : a;
}
LL lcm(LL a, LL b)
{
    return a / gcd(a, b) * b;
}

LLMAP dp[45];

void Gao()
{
    dp[1][1] = 1;
    for(int i = 1; i <= 40; ++i)
    {
        dp[i] = dp[i-1];
        dp[i][i] += 1;
        for(MAP_IT it = dp[i-1].begin(); it != dp[i-1].end(); ++it)
        {
            dp[i][lcm(it->first, i)] += it->second;
        }
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    Gao();
    int T, N, cases = 0;
    long long M;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%I64d", &N, &M);
        LL res = 0LL;
        for(MAP_IT it = dp[N].begin(); it != dp[N].end(); ++it) {
            if(it->first >= M) {
                res += it->second;
            }
        }
        printf("Case #%d: %I64d\n", ++cases, res);
    }
    return 0;
}

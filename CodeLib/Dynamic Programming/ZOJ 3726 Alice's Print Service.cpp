/*
** ZOJ 3726 Alice's Print Service
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;

int N, M;
LL s[MAXN];
LL p[MAXN];
LL dp[MAXN];
LL res;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
	while (T--)
    {
        scanf("%d%d", &N, &M);
        for(int i = 1; i <= N; ++i) {
            scanf("%lld%lld", &s[i], &p[i]);
        }
        dp[N] = s[N] * p[N];
        for(int i = N-1; i >= 1; --i) {
            dp[i] = min(s[i] * p[i], dp[i+1]);
        }
        while(M--) {
            int query;
            LL res = 0LL;
            scanf("%d", &query);
            int k = upper_bound(s + 1, s + 1 + N, query) - s;
            k--;
            if(k == N) {
                res = query * p[N];
            } else {
                res = min(query * p[k], dp[k+1]);
            }
            printf("%lld\n", res);
        }
	}
	return 0;
}

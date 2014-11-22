/*
** UVA 11825 Hackers' Crackdown
** Created by Rayn @@ 2014/09/03
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 17;

int net[MAXN];
int cover[1 << 16];
int dp[1 << 16];

string toBinary(int x)
{
    string ret;
    while(x) {
        ret = (char)(x % 2 + '0') + ret;
        x /= 2;
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, m, cases = 0;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%d", &m);
            net[i] = 1 << i;
            for(int j = 0, x; j < m; ++j) {
                scanf("%d", &x);
                net[i] |= 1 << x;
            }
        }
        memset(cover, 0, sizeof(cover));
        for(int s = 0; s < (1 << n); ++s) {
            for(int i = 0; i < n; ++i) {
                if(s & (1 << i)) {
                    cover[s] |= net[i];
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        int ALL = (1 << n) - 1;
        for(int s = 1; s < (1 << n); ++s) {
            for(int sub = s; sub; sub = s & (sub - 1)) {
                if(cover[sub] == ALL) {
                    dp[s] = max(dp[s], dp[s^sub] + 1);
                }
            }
        }
        printf("Case %d: %d\n", ++cases, dp[ALL]);
    }
    return 0;
}

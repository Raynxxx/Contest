/*
** ZOJ 3812 We Need Medicine
** Created by Rayn @@ 2014/09/09
*/
#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 410;
const int MAXP = 42;
const int MAXW = 52;
const int MAXS = 200001;

int n, q, cnt;
int sz, ok;
int w[MAXN], t[MAXN];
int res[MAXN];
bitset<MAXS> dp[MAXW];
bitset<MAXS> path[MAXP][MAXW];

void Init()
{
    for(int i = 0; i <= 50; ++i) {
        dp[i].reset();
    }
}
bool dfs(int n, int m, int s)
{
    if(ok) return true;
    if(m == 0 && s == 0) {
        ok = 1;
        return true;
    }
    int now = n / 10 + (n % 10 ? 1 : 0);
    if(path[now][m][s] == 0) {
        return false;
    }
    if(m >= w[n] && s >= t[n]) {
        res[sz++] = n;
        if(!dfs(n-1, m-w[n], s-t[n])) {
            sz--;
        }
    }
    return dfs(n-1, m, s);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        Init();
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", &w[i], &t[i]);
        }
        dp[0].set(0, 1);
        for(int i = 1, cnt = 0; i <= n; ++i) {
            for(int j = 50; j >= w[i]; --j) {
                dp[j] |= (dp[j - w[i]] << t[i]);
            }
            if(i % 10 == 0 || i == n) {
                ++cnt;
                for(int j = 0; j <= 50; ++j) {
                    path[cnt][j] = dp[j];
                }
            }
        }
        while(q--)
        {
            int m, s;
            scanf("%d%d", &m, &s);
            if(dp[m][s] == 1) {
                sz = ok = 0;
                dfs(n, m, s);
                for(int i = 0; i < sz; ++i) {
                    printf("%d%c", res[i], (i == sz-1)? '\n' : ' ');
                }
            } else {
                printf("No solution!\n");
            }
        }
    }
	return 0;
}

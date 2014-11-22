/*
** ZOJ 3381 Osaisen Choudai!(RMQ)
** Created by Rayn @@ 2014/08/28
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50005;
const int MAXP = 15;

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    return ret;
}

int N;
int s[MAXN], x[MAXN], y[MAXN];
int dp[MAXN], ST[MAXN][MAXP];

void Update(int w)
{
    ST[w][0] = dp[w];
    for(int i = 1; w + (1 << i) - 1 <= N; ++i)
    {
        ST[w][i] = max(ST[w][i-1], ST[w + (1 << (i-1))][i-1]);
    }
}

int getMax(int L, int R)
{
    if(L > R) return 0;
    int s = 0;
    while((1 << (s+1)) <= R-L+1) {
        s++;
    }
    return max(ST[L][s], ST[R-(1 << s)+1][s]);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &N) != EOF)
    {
        memset(ST, 0, sizeof(ST));
        for(int i = 1; i <= N; ++i)
        {
            s[i] = nextInt();
            x[i] = nextInt();
            y[i] = nextInt();
        }
        for(int i = N; i >= 1; --i)
        {
            int l = i + x[i];
            int r = min(i + y[i] - 1, N);
            dp[i] = s[i] + getMax(l, r);
            Update(i);
        }
        printf("%d\n", dp[1]);
    }
    return 0;
}

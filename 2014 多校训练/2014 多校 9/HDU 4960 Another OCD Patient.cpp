/*
** HDU 4960 Another OCD Patient
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#define MOD 998244353
using namespace std;
typedef long long LL;
typedef long long LL;
const int maxn = 5010;

template <typename T>
inline void FastRead(T& ret)
{
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

int v[maxn], a[maxn];
int dp[maxn][maxn];
long long presum[maxn];

int Solve(int L, int R)
{
    if(dp[L][R] != -1) return dp[L][R];
    if(L >= R) return dp[L][R] = 0;

    dp[L][R] = a[R-L+1];
    int i = L;
    for(int j = R; j >= L; j--)
    {
        while(presum[i] - presum[L-1] < presum[R] - presum[j-1])
            i++;
        if(i == j) break;
        if(presum[i] - presum[L-1] == presum[R] - presum[j-1])
        {
            dp[L][R] = min(dp[L][R], a[i-L+1] + Solve(i+1, j-1) + a[R-j+1]);
        }
    }
    return dp[L][R];
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N;
    while(scanf("%d", &N) != EOF && N)
    {
        presum[0] = 0;
        for(int i = 1; i <= N; ++i) {
            FastRead(v[i]);
            presum[i] = presum[i-1] + v[i];
        }
        for(int i = 1; i <= N; ++i) {
            FastRead(a[i]);
        }
        memset(dp, -1, sizeof(dp));
        printf("%d\n", Solve(1, N));
    }
    return 0;
}

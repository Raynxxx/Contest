/*
** HDU 4961 Boring Sum
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

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

int a[MAXN];
int b[MAXN];
int c[MAXN];
int vis[MAXN];
vector<int> fact[MAXN];

void getFactor()
{
    for(int i = 1; i < MAXN; ++i) {
        for(int j = i; j < MAXN; j += i) {
            fact[j].push_back(i);
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    getFactor();
    int n;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 1; i <= n; ++i) {
            FastRead(a[i]);
        }
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i)
        {
            int u = a[i];
            b[i] = (vis[u] == 0)? a[i] : a[vis[u]];
            for(int j = 0; j < (int)fact[u].size(); ++j)
            {
                vis[fact[u][j]] = max(vis[fact[u][j]], i);
            }
        }
        memset(vis, INF, sizeof(vis));
        for(int i = n; i >= 0; --i)
        {
            int u = a[i];
            c[i] = (vis[u] == INF)? a[i] : a[vis[u]];
            for(int j = 0; j < (int)fact[u].size(); ++j)
            {
                vis[fact[u][j]] = min(vis[fact[u][j]], i);
            }
        }
        LL ret = 0LL;
        for(int i = 1; i <= n; ++i)
        {
            ret += (LL)b[i] * c[i];
        }
        printf("%I64d\n", ret);
    }
    return 0;
}

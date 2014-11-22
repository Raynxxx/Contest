/*
** ZOJ 2315 New Year Bonus Grant
** Created by Rayn @@ 2014/08/11
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 500010;

int cheif[maxn], vis[maxn];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i = 2; i <= n; ++i)
        {
            scanf("%d", &cheif[i]);
        }
        memset(vis, 0, sizeof(vis));
        int cnt = 0;
        for(int i = n; i >= 2; --i)
        {
            int p = cheif[i];
            if(vis[p] == 0 && vis[i] == 0)
            {
                cnt++;
                vis[p] = -1;
                vis[i] = 1;
            }
        }
        printf("%d\n", cnt*1000);
        for(int i = 2, j = 0; i <= n; ++i)
        {
            if(vis[i] == 1)
            {
                printf("%d%c", i, (j++ == cnt-1)?'\n':' ');
            }
        }
        if(t > 0)
            printf("\n");
    }
    return 0;
}

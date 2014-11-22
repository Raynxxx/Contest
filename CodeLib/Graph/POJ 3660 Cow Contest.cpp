/*
** POJ 3660 Cow Contest
** Created by Rayn @@ 2014/07/11
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 110;
const int INF = 0x3F3F3F3F;

int win[MAXN][MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, m, a, b;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(win, 0, sizeof(win));
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d", &a, &b);
            win[a][b] = 1;
        }
        for(int k = 1; k <= n; k++)
        {
            for(int i = 1; i <= n; ++i)
            {
                for(int j = 1; j <= n; ++j)
                {
                    win[i][j] = win[i][j] || (win[i][k] && win[k][j]);
                }
            }
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            int tot = 0;
            for(int j = 1; j <= n; ++j)
            {
                if(win[i][j] || win[j][i])
                    tot++;
            }
            if(tot == n-1)
                cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}

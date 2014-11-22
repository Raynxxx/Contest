/*
** HDU 3665 Seaside
** Created by Rayn @@ 2014/07/08
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;
const int INF = 0x3F3F3F3F;
const int MAXN = 15;

int Map[MAXN][MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, m, isNear, dis;
    int from, to;

    while(scanf("%d", &n) != EOF)
    {
        memset(Map, INF, sizeof(Map));
        for(from = 0; from < n; ++from)
        {
            scanf("%d%d", &m, &isNear);
            if(isNear)
                Map[from][n] = 0;
            for(int i = 0; i < m; ++i)
            {
                scanf("%d%d", &to, &dis);
                Map[from][to] = dis;
            }
        }
        for(int k = 0; k <= n; ++k)
        {
            for(int i = 0; i <= n; ++i)
            {
                for(int j = 0; j <= n; ++j)
                {
                    if(Map[i][k] != INF && Map[k][j] != INF)
                    {
                        Map[i][j] = min(Map[i][j], Map[i][k] + Map[k][j]);
                    }
                }
            }
        }
        printf("%d\n", Map[0][n]);
    }
    return 0;
}

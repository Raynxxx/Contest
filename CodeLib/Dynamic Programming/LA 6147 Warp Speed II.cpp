/*
** LA 6147 Warp Speed II
** Created by Rayn @@ 2014/08/05
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
const int maxn = 105;
const int maxm = 1005;
const int INF = 0x3F3F3F3F;

int n, m, tot, x;
int v1[maxm][maxm], v2[maxm][maxm];
int dp[maxm][maxm], path[maxm][maxm];
int state[maxm], tmp[maxm], put[maxm];
char str[maxm*maxm];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                scanf("%d", &v1[i][j]);
            }
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                scanf("%d", &v2[i][j]);
            }
        }
        scanf("%*c%*c");
        while(gets(str) && strlen(str))
        {
            tot = 0;
            istringstream sstream(str);
            while (sstream >> x)
            {
                tmp[++tot] = x;
            }
            for(int i = 1; i <= tot; i++)
            {
                state[i] = tmp[tot-i+1];
            }

            for(int i = 0; i < n; i++)
            {
                dp[0][i] = (i == 0)? 0 : INF;
            }
            for(int i = 1; i <= tot; i++)
            {
                dp[i][0] = INF;
                for(int j = 1; j < n; j++)
                {
                    dp[i][j] = INF;
                    for(int k = 0; k < n; k++)
                    {
                        if(dp[i-1][k] + v1[j][k] < dp[i][j])
                        {
                            dp[i][j] = dp[i-1][k] + v1[j][k];
                            path[i][j] = k;
                        }
                    }
                    dp[i][j] += v2[j][state[i]];
                }
            }

            int ans = INF, last;
            for(int j = 1; j < n; j++)
            {
                if (dp[tot][j] + v1[0][j] < ans)
                {
                    ans = dp[tot][j] + v1[0][j];
                    last = j;
                }
            }

            printf("%d\n", ans);
            int i = tot, j = last;
            tot = 0;
            while(i > 0) {
                put[++tot] = j;
                j = path[i][j];
                i--;
            }
            for(int i = 1; i <= tot; i++)
            {
                printf("%d%c", put[i], (i == tot)?'\n':' ');
            }
        }
    }
    return 0;
}

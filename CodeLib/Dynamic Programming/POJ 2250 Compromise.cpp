/*
** POJ 2250 Compromise
** Created by Rayn @@ 2014/05/06
** 最长公共子序列
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 110;

int dp[MAX][MAX], path[MAX];
char str1[MAX][32], str2[MAX][32];

int main()
{
    int cnt1 = 1, cnt2 = 1;

    while(scanf("%s", str1[cnt1]) != EOF)
    {
        cnt1++;
        while(scanf("%s", str1[cnt1]) && str1[cnt1][0] != '#')
        {
            cnt1++;
        }
        while(scanf("%s", str2[cnt2]) && str2[cnt2][0] != '#')
        {
            cnt2++;
        }
        memset(dp, 0, sizeof(dp));
        memset(path, 0, sizeof(path));
        for(int i=1; i<cnt1; ++i)
        {
            for(int j=1; j<cnt2; ++j)
            {
                if(strcmp(str1[i], str2[j]) == 0)
                {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        int i = cnt1-1, j = cnt2-1, k = 0;
        while(i > 0 && j > 0)
        {
            if(strcmp(str1[i], str2[j]) == 0)
            {
                path[k++] = i;
                i--; j--;
            }
            else if(dp[i][j] == dp[i-1][j])
            {
                i--;
            }
            else if(dp[i][j] == dp[i][j-1])
            {
                j--;
            }
        }
        if(k > 0)
        {
            printf("%s", str1[path[k-1]]);
            for(int i=k-2; i>=0; --i)
                printf(" %s", str1[path[i]]);
            printf("\n");
        }
        cnt1 = cnt2 = 1;
    }
    return 0;
}

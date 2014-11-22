/*
** UVA 111 History Grading
** Created by Rayn @@ 2014/04/24
** 最长公共子序列（LCS）
** 题意有点难理解，给出的c1,c2...cn中ci是事件i发生的年份
** 学生输入的是r1,r2...rn中ri是事件i发生的年份
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 25;

int order[MAXN], stu[MAXN];
int dp[MAXN][MAXN];

int main()
{
    int N, k;

    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d", &k);
        order[k] = i;
    }
    while(scanf("%d", &k) != EOF)
    {
        stu[k] = 1;
        for(int i=2; i<=N; ++i)
        {
            scanf("%d", &k);
            stu[k] = i;
        }

        memset(dp, -1, sizeof(dp));
        for(int i=0; i<=N; ++i)
            dp[i][0] = dp[0][i] = 0;
        for(int i=1; i<=N; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                if(order[i] == stu[j])
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        printf("%d\n", dp[N][N]);
    }
    return 0;
}

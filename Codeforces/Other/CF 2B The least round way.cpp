/*
** CodeForces 2B The least round way
** Created by Rayn @@ 2014/05/29
*/
#include <cstdio>
#include <cstring>
const int MAX = 1010;
const int INF = 0x3F3F3F3F;

int mat;
int path[MAX][MAX][2];
int num[MAX][MAX][2];
int dp[MAX][MAX][2];

void PrintPath(int d, int x, int y)
{
    if(x == 0 && y == 0)
        return ;
    if(path[x][y][d] == 0)
    {
        PrintPath(d, x-1, y);
        printf("D");
    }
    else if(path[x][y][d] == 1)
    {
        PrintPath(d, x, y-1);
        printf("R");
    }
}
int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
    {
        int flag = 0, zero, tmp, cnt;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                dp[i][j][0] = dp[i][j][1] = INF;
                scanf("%d", &mat);
                if(mat == 0)
                {
                    flag = 1;
                    zero = i;   //记录0所在行数
                    continue;
                }
                tmp = mat; cnt = 0;
                while(tmp%2 == 0)
                {
                    cnt++;
                    tmp /= 2;
                }
                num[i][j][0] = cnt; //记录a可分解2的个数
                tmp = mat; cnt = 0;
                while(tmp%5 == 0)
                {
                    cnt++;
                    tmp /= 5;
                }
                num[i][j][1] = cnt;;//记录a可分解5的个数
            }
        }
        dp[0][0][0] = num[0][0][0];
        dp[0][0][1] = num[0][0][1];
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i >= 1)
                {
                    if(dp[i][j][0] > dp[i-1][j][0] + num[i][j][0])
                    {
                        dp[i][j][0] = dp[i-1][j][0] + num[i][j][0];
                        path[i][j][0] = 0;
                    }
                    if(dp[i][j][1] > dp[i-1][j][1] + num[i][j][1])
                    {
                        dp[i][j][1] = dp[i-1][j][1] + num[i][j][1];
                        path[i][j][1] = 0;
                    }
                }
                if(j >= 1)
                {
                    if(dp[i][j][0] > dp[i][j-1][0] + num[i][j][0])
                    {
                        dp[i][j][0] = dp[i][j-1][0] + num[i][j][0];
                        path[i][j][0] = 1;
                    }
                    if(dp[i][j][1] > dp[i][j-1][1] + num[i][j][1])
                    {
                        dp[i][j][1] = dp[i][j-1][1] + num[i][j][1];
                        path[i][j][1] = 1;
                    }
                }
            }
        }
        int k = (dp[n-1][n-1][0] < dp[n-1][n-1][1])? 0 : 1;
        //如果有0，而且求得的最小值大于1，就选择经过0的一条路径
        if(flag == 1 && dp[n-1][n-1][k] > 1)
        {
            printf("1\n");
            for(int i = 0; i < zero; ++i)
                printf("D");
            for(int i = 1; i < n; ++i)
                printf("R");
            for(int i = zero+1; i < n; ++i)
                printf("D");
        }
        else
        {
            printf("%d\n", dp[n-1][n-1][k]);
            PrintPath(k, n-1, n-1);
        }
        printf("\n");
    }
	return 0;
}

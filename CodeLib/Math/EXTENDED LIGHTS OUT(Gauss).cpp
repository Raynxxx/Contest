/*
** EXTENDED LIGHTS OUT
** Created by Rayn @@ 2014/3/20
** 特地学习了一下高斯消元，wiki还有伪代码
** 当初线性代数课就不该睡觉的
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 35
#define N 10
using namespace std;

int ans[MAX], light[N][N], matrix[MAX][MAX];
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

int gcd(int m, int n);
int lcm(int m, int n);
void Gauss();

int main()
{
    int n, cases = 0;

    scanf("%d", &n);
    while(n--)
    {
        for(int i=0; i<5; ++i)
        {
            for(int j=0; j<6; ++j)
                scanf("%d", &light[i][j]);
        }

        memset(matrix, 0, sizeof(matrix));
        for(int i=0; i<5; ++i)
        {
            for(int j=0; j<6; ++j)
            {
                int row = i * 6 + j;
                matrix[row][row] = 1;
                matrix[row][30] = light[i][j];
                for(int k=0; k<4; ++k)
                {
                    int ti = i + dir[k][0];
                    int tj = j + dir[k][1];
                    if(ti >= 0 && ti < 5 && tj >=0 && tj < 6)
                        matrix[row][ti*6+tj] = 1;
                }
            }
        }

        Gauss();

        printf("PUZZLE #%d\n", ++cases);
        for(int i=0; i<30; ++i)
        {
            printf("%d", ans[i]);
            if(i % 6 != 5)
                printf(" ");
            else
                printf("\n");
        }
    }
}

int gcd(int m, int n)
{
    if(n == 0)
        return m;
    else
        return gcd(n, m%n);
}
int lcm(int m, int n)
{
    return m * n / gcd(m, n);
}
void Gauss()
{

    for(int row=0, col=0; row<30 && col<30; ++row,++col)
    {
        int max_row = row;
        for(int j=row+1; j<30; ++j)
        {
            if (abs(matrix[j][col]) > abs(matrix[max_row][col]))
            {
                max_row = j;
                break;
            }
        }
        if(matrix[max_row][col] == 0)
        {
            row--;
            continue;
        }
        if(row != max_row)
        {
            for (int j=col; j<=30; ++j)
                swap(matrix[row][j],matrix[max_row][j]);
        }
        for(int i=row+1; i<30; ++i)
        {
            if(matrix[i][col])
            {
                for(int j = col; j <= 30; ++j)
                    matrix[i][j] ^= matrix[row][j];
            }
        }
    }
    for(int i=29; i>=0; --i)
    {
        ans[i] = matrix[i][30];
        for(int j=i+1; j<30; ++j)
            ans[i] ^= (matrix[i][j] && ans[j]);
    }
}


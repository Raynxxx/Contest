/*
** POJ 1948 Triangular Pastures
** Created by Rayn @@ 2014/04/22
** ¶þÎ¬01±³°ü
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 810;

int tot;
int len[50];
int dp[MAX][MAX];

double GetArea(int a, int b, int c)
{
    double p = tot/2.0;
    double area = 100 * sqrt(p*(p-a)*(p-b)*(p-c));
    return area;
}
int main()
{
    int N;

    scanf("%d", &N);
    tot = 0;
    for(int i=0; i<N; ++i)
    {
        scanf("%d", &len[i]);
        tot += len[i];
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i=0; i<N; ++i)
    {
        for(int j=tot/2; j>=0; --j)
        {
            for(int k=tot/2; k>=0; --k)
            {
                if((j>=len[i] && dp[j-len[i]][k]) || (k>=len[i]&&dp[j][k-len[i]]))
                    dp[j][k] = 1;
            }
        }
    }
    int maxa = -1;
    for(int i=1; i<tot/2; ++i)
    {
        for(int j=1; j<tot/2; ++j)
        {
            if(dp[i][j] == 1)
            {
                int k = tot - i - j;
                if(i+j>k && i+k>j && j+k>i)
                {
                    maxa = max(maxa, (int)GetArea(i, j, k));
                }
            }
        }
    }
    printf("%d\n",maxa);
    return 0;
}

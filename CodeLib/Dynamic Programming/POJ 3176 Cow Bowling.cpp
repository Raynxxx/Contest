/*
** POJ 3176 Cow Bowling
** Created by Rayn @@ 2014/04/21
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 400;

int arr[MAX][MAX], dp[MAX][MAX];

int main()
{
    int i, j, N;

    while(scanf("%d", &N) != EOF && N)
    {
        for(i=0; i<N; ++i)
        {
            for(j=0; j<=i; ++j)
            {
                scanf("%d", &arr[i][j]);
            }
        }
        for(j=0; j<N; ++j)
        {
            dp[N-1][j] = arr[N-1][j];
        }
        for(i=N-2; i>=0; --i)
        {
            for(j=0; j<=i; ++j)
            {
                dp[i][j] = arr[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
            }
        }
        printf("%d\n", dp[0][0]);

    }
    return 0;
}

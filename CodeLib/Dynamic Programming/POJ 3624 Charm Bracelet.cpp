/*
** POJ 3624 Charm Bracelet
** Created by Rayn @@ 2014/04/25
** 01背包，太简单的模板题
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int w[3500], d[3500], dp[13000];

int main()
{
	int N, M;

	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i)
    {
        scanf("%d%d", &w[i], &d[i]);
    }
    memset(dp, 0, sizeof(dp));
    for(int i=0; i<N; ++i)
    {
        for(int j=M; j>=w[i]; --j)
        {
            dp[j] = max(dp[j], dp[j-w[i]]+d[i]);
        }
    }
    printf("%d\n",dp[M]);
	return 0;
}

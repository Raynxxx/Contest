/*
** ZOJ 3802 Easy 2048 Again
** Created by Rayn @@ 2014/09/05
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 510;
const int MAXS = (1 << 13);

int N, res;
int arr[MAXN];
int dp[2][MAXS];

int Gao()
{

    int cur = 0, pre = 1;
    memset(dp[cur], -1, sizeof(dp[cur]));
    res = dp[cur][0] = 0;
    for(int i = 1; i <= N; ++i) {
        swap(cur, pre);
        memset(dp[cur], -1, sizeof(dp[cur]));
        for(int j = 0; j < (1 << 13); ++j) {
            if(dp[pre][j] == -1) continue ;
            dp[cur][j] = max(dp[cur][j], dp[pre][j]);
            int status;
            if(j & (arr[i] - 1)) {
                status = arr[i];
            } else {
                status = j + arr[i];
            }
            int now = arr[i], score = arr[i];
            if((j & (arr[i] - 1)) == 0) {
                int mask = j;
                while(mask & now) {
                    mask -= now;
                    now <<= 1;
                    score += now;
                }
            }
            dp[cur][status] = max(dp[cur][status], dp[pre][j] + score);
            res = max(res, dp[cur][status]);
        }
    }
    return res;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", Gao());
    }
	return 0;
}

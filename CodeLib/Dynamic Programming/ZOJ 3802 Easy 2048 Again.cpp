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
const int MAXS = (1 << 12) + 10;

int N;
int arr[MAXN];
int dp[2][MAXS];
int pow2[15];
int prelog2[MAXS];

void getPower() {
    pow2[0] = 1;
    for(int i = 1; i <= 12; ++i) {
        pow2[i] = pow2[i-1] * 2;
        prelog2[pow2[i]] = i;
    }
}
int Gao()
{
    memset(dp, -1, sizeof(dp));
    int cur = 0, pre = 1;
    int pos, mask;
    dp[cur][0] = 0;
    for(int i = 1; i <= N; ++i) {
        swap(cur, pre);
        for(int j = 0; j < (1 << 12); ++j) {
            if(dp[pre][j] != -1) {
                dp[cur][j] = max(dp[cur][j], dp[pre][j]);
                int status = j, score = arr[i];
                pos = prelog2[arr[i]] - 1;
                mask = (1 << pos) - 1;
                if((status & mask) == 0) {
                    while(status & (1 << pos)) {
                        score += pow2[pos+2];
                        pos++;
                    }
                    mask = (1 << pos) - 1;
                    status &= (~mask);
                    status |= (1 << pos);
                } else {
                    status = (1 << pos);
                }
                dp[cur][status] = max(dp[cur][status], dp[pre][j] + score);
            }
        }
    }
    int res = 0;
    for(int i = 0; i < (1 << 12); ++i) {
        res = max(res, dp[cur][i]);
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
    getPower();
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

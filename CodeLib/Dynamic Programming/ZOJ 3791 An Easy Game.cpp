/*
** ZOJ 3791 An Easy Game
** Created by Rayn @@ 2014/08/12
** ��dp[i][j]��ʾ��i������ǰ����j��λ��
** ��Ŀ�괮��ͬ����Ϊdp[k][0].
** ���Կ��Խ�j��λ���е�k��λ�ñ�Ϊ��Ŀ
** �괮��ͬ��������n-j��λ���е�m-k��λ
** �ñ�Ϊ��Ŀ�괮��ͬ
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 105;
const int MOD = 1000000009;

int N, K, M;
char s1[MAXN], s2[MAXN];
int comb[MAXN][MAXN];
int dp[MAXN][MAXN];

void getComb()
{
    memset(comb, 0, sizeof(comb));
    comb[0][0] = 1;
    for(int i = 1; i < MAXN; ++i)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; j++)
        {
            comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % MOD;
        }
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    getComb();
    while(scanf("%d%d%d", &N, &K, &M) != EOF)
    {
        scanf("%s%s", s1, s2);
        int diff = 0;
        for(int i = 0; i < N; ++i) {
            diff += (s1[i] != s2[i]);
        }
        memset(dp, 0, sizeof(dp));
        dp[0][diff] = 1;
        for (int i = 1; i <= K; ++i) {
            for (int j = 0; j <= N; ++j) {
                for (int k = 0; k <= M && k <= j; ++k) {
                    if(N-j < M-k) continue;
                    dp[i][j-k+M-k] += ((LL)dp[i-1][j] * comb[j][k]) % MOD * comb[N-j][M-k] % MOD;
                    dp[i][j-k+M-k] %= MOD;
                }
            }
        }
        printf("%d\n", dp[K][0]);
    }
    return 0;
}

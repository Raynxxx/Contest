/*
** ZOJ 3797 Sister's Noise
** Created by Rayn @@ 2014/08/16
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL INF = 1LL << 60;
const int MAXN = 40;
const int MAXL = 400;
const int MAXT = 15;

struct Node
{
    char c;
    int t;
    Node() {}
    Node(char c, int t): c(c), t(t) {}

    bool operator < (const Node& rhs) const
    {
        return c > rhs.c;
    }
};

LL N, M, L;
string ret;
LL comb[MAXL][MAXT];
LL dp[MAXN][MAXL];
Node letter[MAXN];

void getComb()
{
    comb[0][0] = 1LL;
    for(int i = 1; i <= 360; ++i)
    {
        comb[i][0] = 1;
        for(int j = 1; j <= min(10, i); ++j)
        {
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
        }
    }
}
LL Calc(int l)
{
    LL sum[MAXN];
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i <= N; ++i)
    {
        sum[i] = sum[i-1] + letter[i].t;
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1LL;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j <= sum[i]; ++j)
        {
            for(int k = 0; k <= letter[i+1].t; ++k)
            {
                if (dp[i][j] <= INF / comb[j+k][k]) {
                    dp[i+1][j+k] += dp[i][j] * comb[j+k][k];
                } else {
                    dp[i+1][j+k] = INF;
                }
                if (dp[i+1][j+k] > INF) {
                    dp[i+1][j+k] = INF;
                }
            }
        }
    }
    LL res = 0LL;
    for(int i = l; i <= sum[N]; ++i)
    {
        res += dp[N][i];
        if(res > INF) {
            res = INF;
        }
    }
    return res;
}
void Gao(LL m, int l)
{
    for(int i = 1; i <= N; ++i)
    {
        if(letter[i].t)
        {
            letter[i].t--;
            LL tmp = Calc(l-1);
            if (tmp < m) {
                letter[i].t++;
                m -= tmp;
            } else {
                ret += letter[i].c;
                Gao(m, l-1);
                return ;
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char buf[20];
    getComb();
    while(scanf("%lld%lld%lld", &N, &M, &L) != EOF)
    {
        for(int i = 1, t; i <= N; ++i)
        {
            scanf("%s%d", buf, &t);
            letter[i] = Node(buf[0], t);
        }
        sort(letter+1, letter+1+N);
        ret.clear();
        Gao(M, L);
        if(!ret.size())
            printf("-1\n");
        else
            printf("%s\n", ret.c_str());
    }
    return 0;
}

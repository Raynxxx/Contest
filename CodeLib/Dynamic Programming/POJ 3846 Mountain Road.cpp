/*
** POJ 3846 Mountain Road
** Created by Rayn @@ 2014/05/03
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAX = 205;
const int INF = 0x3f3f3f3f;

struct car{
    int t, d;
};

car A[MAX], B[MAX];
int dp[2][MAX][MAX];

int main() {

#ifdef HotWhite
    freopen("in.txt", "r", stdin);
#endif
    int c, n;

    scanf("%d", &c);
    while(c--)
    {
        scanf("%d" ,&n);

        char tmp[5];
        int cntA = 0, cntB = 0;
        for(int i=0; i<n; ++i)
        {
            scanf("%s", tmp);
            if(tmp[0] == 'A')
            {
                cntA++;
                scanf("%d%d", &A[cntA].t, &A[cntA].d);
            }
            else if(tmp[0] == 'B')
            {
                cntB++;
                scanf("%d%d", &B[cntB].t, &B[cntB].d);
            }
        }
        memset(dp, INF, sizeof(dp));
        dp[0][0][0] = dp[1][0][0] = 0;
        int beg, ed;
        for(int i=0; i<=cntA; ++i)
        {
            for(int j=0; j<=cntB; ++j)
            {
                beg = dp[0][i][j]; ed = 0;
                for(int k=i+1; k<=cntA; ++k)
                {
                    beg = max(beg, A[k].t);
                    ed = max(ed, beg + A[k].d);
                    dp[1][k][j] = min(dp[1][k][j], ed);
                    beg += 10;
                    ed += 10;
                }
                beg = dp[1][i][j]; ed = 0;
                for(int k=j+1; k<=cntB; ++k)
                {
                    beg = max(beg, B[k].t);
                    ed = max(ed, beg+B[k].d);
                    dp[0][i][k] = min(dp[0][i][k], ed);
                    beg += 10;
                    ed += 10;
                }
            }
        }
        int ans = min(dp[0][cntA][cntB], dp[1][cntA][cntB]);
        printf("%d\n", ans);

    }
    return 0;
}

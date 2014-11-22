/*
** POJ 1276 Cash Machine
** Created by Rayn @@ 2014/04/22
** 多重背包
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[100010];

int main()
{
    int num, money;
    int cash, N;

    while(scanf("%d%d", &cash, &N) != EOF)
    {
        memset(dp, 0, sizeof(dp));
        for(int i=0; i<N; ++i)
        {
            scanf("%d%d", &num, &money);
            /*
            * 这一份物品不能全部放入取了以后有剩
            * 余，那么对于背包这个物品有无限个.
            * 套用完全背包
            */
            if(num*money >= cash)
            {
                for(int j=money; j<=cash; ++j)
                    dp[j] = max(dp[j], dp[j-money]+money);
                continue;   //少写了这句话也AC了？！
            }
            /*
            * 二进制拆分 转化为01背包
            */
            int k = 1;
            while(k < num)
            {
                int tmp = money*k;
                for(int j=cash; j>=tmp; --j)
                    dp[j] = max(dp[j], dp[j-tmp]+tmp);
                num -= k;
                k = k<<1;
            }
            int tmp = num * money;
            for(int j=cash; j>=tmp; --j)
                dp[j] = max(dp[j], dp[j-tmp]+tmp);
        }
        printf("%d\n", dp[cash]);
    }
    return 0;
}

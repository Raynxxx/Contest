/*
** HDU 4455 Substrings
** Created by Rayn @@ 2014/10/09
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1000005;

int x[MAXN]; // 原数列
int w[MAXN]; // w[i]记录长度为i的后缀数列里面的unique元素的个数
int dp2[MAXN]; // dp[i]记录有多少个元素的前一个相同元素的下标与该元素下标的差是i
LL dp[MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, cc;
    while(scanf("%d", &n) != EOF && n)
    {
        memset(dp, 0, sizeof(dp));
        memset(dp2, 0, sizeof(dp2));
        //预处理
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &x[i]);
            dp2[i-dp[x[i]]]++;
            dp[x[i]] = i;
        }
        cc = 0;
        memset(dp, 0, sizeof(dp));
        for(int i = n; i >= 1; --i)
        {
            if(dp[x[i]] == 0)
                cc++;
            dp[x[i]] = 1;
            w[n-i+1] = cc;  //长度为n-i+1的后缀中不同元素的个数，存入w
        }
        //开始递推
        dp[1] = n;
        cc = n;
        for(int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i-1] - w[i-1];   //减去长度为i-1的后缀数列里面的不同元素的个数
            cc -= dp2[i-1]; //和前一个元素位置差为i-1的元素已经不会再计数，减去
            dp[i] += cc;    //加上新增的不同元素
        }
        //查询
        scanf("%d", &cc);
        while(cc--)
        {
            int i;
            scanf("%d", &i);
            printf("%I64d\n", dp[i]);
        }
    }
    return 0;
}

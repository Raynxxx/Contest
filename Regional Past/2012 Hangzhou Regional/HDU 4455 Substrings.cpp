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

int x[MAXN]; // ԭ����
int w[MAXN]; // w[i]��¼����Ϊi�ĺ�׺���������uniqueԪ�صĸ���
int dp2[MAXN]; // dp[i]��¼�ж��ٸ�Ԫ�ص�ǰһ����ͬԪ�ص��±����Ԫ���±�Ĳ���i
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
        //Ԥ����
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
            w[n-i+1] = cc;  //����Ϊn-i+1�ĺ�׺�в�ͬԪ�صĸ���������w
        }
        //��ʼ����
        dp[1] = n;
        cc = n;
        for(int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i-1] - w[i-1];   //��ȥ����Ϊi-1�ĺ�׺��������Ĳ�ͬԪ�صĸ���
            cc -= dp2[i-1]; //��ǰһ��Ԫ��λ�ò�Ϊi-1��Ԫ���Ѿ������ټ�������ȥ
            dp[i] += cc;    //���������Ĳ�ͬԪ��
        }
        //��ѯ
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

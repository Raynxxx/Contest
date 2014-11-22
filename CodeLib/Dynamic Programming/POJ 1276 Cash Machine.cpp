/*
** POJ 1276 Cash Machine
** Created by Rayn @@ 2014/04/22
** ���ر���
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
            * ��һ����Ʒ����ȫ������ȡ���Ժ���ʣ
            * �࣬��ô���ڱ��������Ʒ�����޸�.
            * ������ȫ����
            */
            if(num*money >= cash)
            {
                for(int j=money; j<=cash; ++j)
                    dp[j] = max(dp[j], dp[j-money]+money);
                continue;   //��д����仰ҲAC�ˣ���
            }
            /*
            * �����Ʋ�� ת��Ϊ01����
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

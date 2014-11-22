/*
** HDU 1394 Minimum Inversion Number
** Created by Rayn @@ 2014/04/14
** �߶���or����or��״����
**
** ##˼·##
** ��ʼ��������������һ�ּ������ʼ���е�������sum
** �����ұȽ�������ֱ���õı����ҵ�sum
** ����a[i](0~~n-1)��ÿŲһ������sum��ȥŲ֮ǰ���ұ�
** ����С�����ĸ�����Ҳ����a[i]����������sum����Ų֮
** ����߱���������ĸ�����Ҳ����n-a[i]-1����������
** Ų��a[i]֮����������ˡ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 5010;
int arr[MAX], ans;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int N;
    while(scanf("%d", &N) != EOF && N)
    {
        for(int i=0; i<N; ++i)
        {
            scanf("%d", &arr[i]);
        }
        int sum = 0;
        for(int i=0; i<N; ++i)
        {
            for(int j=i+1; j<N; ++j)
            {
                if(arr[i] > arr[j])
                        sum++;
            }
        }
        ans = sum;
        for(int i=0; i<N-1; ++i)
        {
            sum = (sum - arr[i]) + (N - arr[i] - 1);
            ans = min(ans, sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}

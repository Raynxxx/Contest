/*
** UVA 11136 Hoax or what
** Created by Rayn @@ 2014/04/04
** ���ȶ���STL--ά�����Ѻ���С��
** ע��ɾ���ڵ�Ĳ�����ʹ�ñ������
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 1000010;
int maxflag[MAX], minflag[MAX];
priority_queue<int, vector<int>, greater<int> > minq;   //��С��
priority_queue<int, vector<int>, less<int> > maxq;  //����

int main()
{
    int n, k;

    while(scanf("%d", &n) != EOF && n)
    {
        memset(maxflag, 0, sizeof(maxflag));
        memset(minflag, 0, sizeof(minflag));
        while(!minq.empty())
            minq.pop();
        while(!maxq.empty())
            maxq.pop();

        long long ans = 0;
        while(n--)
        {
            scanf("%d", &k);
            for(int i=0; i<k; ++i)
            {
                int input;
                scanf("%d", &input);
                minq.push(input);
                maxq.push(input);
            }
            while(minflag[maxq.top()] > 0)
            {
                minflag[maxq.top()]--;
                maxq.pop();
            }
            while(maxflag[minq.top()] > 0)
            {
                maxflag[minq.top()]--;
                minq.pop();
            }
            maxflag[maxq.top()]++;
            minflag[minq.top()]++;
            ans += maxq.top() - minq.top();
            maxq.pop();
            minq.pop();
        }
        printf("%lld\n", ans);
    }
    return 0;
}

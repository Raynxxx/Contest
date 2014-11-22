/*
** UVA 11987 Almost Union-Find
** Created by Rayn @@ 2014/04/07
** ����2ʵ�����൱���Ȱ�xɾ��Ȼ���ٺ�y�ϲ�����˺�
** ��ͨ�Ĳ��鼯���ֻ�Ƕ���һ��ɾ��ĳ����Ĳ�����
**
**  ����ɾ��x�Ĳ������ǲ������ı�ԭ������pa[x]��ָ��
** �ģ��Ƚ������ܹ��ٳ���������ʵ����ֻ�����ڲ�Ӱ����
** ��Ԫ�ص�ǰ���°�xɾ���������绻��˼·����x������
** �����ڵļ��ϵġ�Ӱ�족��Ϊ0��Ȼ�����¿�һ���ڵ��ʾx��
** �������൱�ڰ�x��ԭ���ļ����а�������ˡ�������ԭ
** ���Ĳ��鼯����Ҫ��һ��id[x]�����ʾ��x���ڵı�ţ���
** �������˼·����Ĳ����Ͳ���д������
*/
#include <cstdio>
using namespace std;
const int MAX = 200010;
int pa[MAX], num[MAX], id[MAX], cnt;
long long rnk[MAX];

int FindSet(int x)
{
    if(x != pa[x])
    {
        pa[x] = FindSet(pa[x]);
    }
    return pa[x];
}
int main()
{
    int n, m;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        cnt = n;
        for(int i=1; i<=n; ++i)
        {
            id[i] = pa[i] = rnk[i] = i;
            num[i] = 1;
        }

        int order, x, y;
        while(m--)
        {
            scanf("%d", &order);
            if(order == 1)
            {
                scanf("%d %d", &x, &y);
                int tx = FindSet(id[x]);
                int ty = FindSet(id[y]);
                if(tx != ty)
                {
                    pa[tx] = ty;
                    num[ty] += num[tx];
                    rnk[ty] += rnk[tx];
                }
            }
            else if(order == 2)
            {
                scanf("%d %d", &x, &y);
                int tx = FindSet(id[x]);
                int ty = FindSet(id[y]);
                if(tx != ty)
                {
                    num[tx]--;
                    rnk[tx] -= x;
                    id[x] = ++cnt;
                    pa[id[x]] = id[x];
                    num[id[x]] = 1;
                    rnk[id[x]] = x;
                    int tx = FindSet(id[x]);
                    pa[tx] = ty;
                    num[ty] += num[tx];
                    rnk[ty] += rnk[tx];
                }
            }
            else if(order == 3)
            {
                scanf("%d", &x);
                int tx = FindSet(id[x]);
                printf("%d %lld\n", num[tx], rnk[tx]);
            }
        }
    }
    return 0;
}

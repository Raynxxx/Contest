/*
** POJ 2828 Buy Tickets
** Created by Rayn @@ 2014/05/08
** ���⣡�߶��������������˼ά
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 200005;

int pos[MAX], val[MAX], ans[MAX];
int tree[MAX*3], index;

void Build(int k, int l, int r)
{
    tree[k] = r - l + 1;    //��ʼʱÿ���ڵ㶼�п�λ
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    Build(k<<1, l, mid);
    Build(k<<1|1, mid+1, r);
}
void Update(int k, int l, int r, int pos)
{
    tree[k]--;  //������£�����һ����λ
    if(l == r)
    {
        index = l;
        return ;
    }
    int mid = (l + r) >> 1;
    if(tree[k<<1] >= pos)   //�����ǰλ�õ���߿�λ���Ļ����������
    {
        Update(k<<1, l, mid, pos);
    }
    else
    {
        pos -= tree[k<<1];  //���򣬾Ͱ���ߵĿ�λ��ȥ�������ұ߶�λ
        Update(k<<1|1, mid+1, r, pos);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r",stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        Build(1, 1, n);
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d", &pos[i], &val[i]);
        }
        for(int i=n; i>=1; --i)
        {
            Update(1, 1, n, pos[i]+1);
            ans[index] = val[i];
        }
        for(int i=1; i<=n; ++i)
        {
            printf("%d%c", ans[i], (i == n)? '\n':' ');
        }
    }
    return 0;
}

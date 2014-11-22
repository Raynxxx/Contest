/*
** POJ 2828 Buy Tickets
** Created by Rayn @@ 2014/05/08
** ��״����ĸ߼�Ӧ��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 200005;

int n, pos[MAX], val[MAX];
int tree[MAX], ans[MAX];

inline int Lowbit(int x)
{
    return x&(-x);
}
void Del(int idx)
{
    while(idx <= n)
    {
        tree[idx]--;
        idx +=Lowbit(idx);
    }
}
// ��״����߼�Ӧ��,�Ҳ��ֺ�ΪK�ĵ�һ��λ��
int SumSeek(int K)
{
    int pos = 0, cnt = 0;
    for(int i=18; i>=0; --i)
    {
        pos += (1 << i);
        if(pos>=n || cnt+tree[pos]>=K)
            pos -= (1 << i);
        else
            cnt += tree[pos];
    }
    return pos+1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d", &n) != EOF)
    {
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d", &pos[i], &val[i]);
            tree[i] = Lowbit(i);    //����λ�����1�������п�λ
        }
        for(int i=n; i>=1; --i)
        {
            int index = SumSeek(pos[i]+1);
            ans[index] = val[i];
            Del(index);
        }
        for(int i=1; i<=n; ++i)
        {
            printf("%d%c", ans[i], (i == n)? '\n':' ');
        }
    }
    return 0;
}

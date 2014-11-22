/*
** POJ 2828 Buy Tickets
** Created by Rayn @@ 2014/05/08
** 神题！线段树，奇妙的逆向思维
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
    tree[k] = r - l + 1;    //开始时每个节点都有空位
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    Build(k<<1, l, mid);
    Build(k<<1|1, mid+1, r);
}
void Update(int k, int l, int r, int pos)
{
    tree[k]--;  //单点更新，减少一个空位
    if(l == r)
    {
        index = l;
        return ;
    }
    int mid = (l + r) >> 1;
    if(tree[k<<1] >= pos)   //如果当前位置的左边空位够的话就落在左边
    {
        Update(k<<1, l, mid, pos);
    }
    else
    {
        pos -= tree[k<<1];  //否则，就把左边的空位减去，再在右边定位
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

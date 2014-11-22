/*
** POJ 2828 Buy Tickets
** Created by Rayn @@ 2014/05/08
** 树状数组+二分
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
int GetSum(int idx)
{
    int sum = 0;
    while(idx > 0)
    {
        sum += tree[idx];
        idx -= Lowbit(idx);
    }
    return sum;
}
void Update(int idx, int val)
{
    while(idx <= n)
    {
        tree[idx] += val;
        idx += Lowbit(idx);
    }
}
int Search(int left, int right, int pos)
{
    while(left <= right)
    {
        int mid = (left + right) >> 1;
        int tmp = GetSum(mid);
        if(tmp == pos && ans[mid] == -1)
            return mid;
        if(tmp >= pos)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d", &n) != EOF)
    {
        memset(tree, 0, sizeof(tree));
        memset(ans, -1, sizeof(ans));
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d", &pos[i], &val[i]);
            pos[i]++;
            Update(i, 1);    //所有位置填充1，代表有空位
        }
        for(int i=n; i>=1; --i)
        {
            int index = Search(pos[i], n, pos[i]);
            ans[index] = val[i];
            Update(index, -1);
        }
        for(int i=1; i<=n; ++i)
        {
            printf("%d%c", ans[i], (i == n)? '\n':' ');
        }
    }
    return 0;
}

/*
** POJ 2352 Stars
** Created by Rayn @@ 2014/04/09
** 树状数组
** 由于Lowbit(0) = 0，这会导致x递增的那条路径
** 发生死循环，所有当树状数组中可能出现0时，
** 我们都全部加一。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 32010;
const int MAXN = 15010;

int tree[MAX], level[MAXN];

inline int lowbit(int idx)
{
    return idx & (-idx);
}
int ReadSum(int idx)
{
    int sum = 0;
    while(idx > 0)
    {
        sum += tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}
void Update(int idx, int val)
{
    while(idx <= MAX)
    {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}
int main()
{
    int n, x, y;

    scanf("%d", &n);

    memset(tree, 0, sizeof(tree));
    memset(level, 0, sizeof(level));
    for(int i=1; i<=n; ++i)
    {
        scanf("%d%d", &x, &y);
        int cnt = ReadSum(++x); //这里超时的原因，如果x=0，发生死循环
        level[cnt]++;
        Update(x, 1);
    }
    for(int i=0; i<n; ++i)
        printf("%d\n", level[i]);
    return 0;
}

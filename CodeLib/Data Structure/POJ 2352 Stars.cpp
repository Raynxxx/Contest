/*
** POJ 2352 Stars
** Created by Rayn @@ 2014/04/09
** ��״����
** ����Lowbit(0) = 0����ᵼ��x����������·��
** ������ѭ�������е���״�����п��ܳ���0ʱ��
** ���Ƕ�ȫ����һ��
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
        int cnt = ReadSum(++x); //���ﳬʱ��ԭ�����x=0��������ѭ��
        level[cnt]++;
        Update(x, 1);
    }
    for(int i=0; i<n; ++i)
        printf("%d\n", level[i]);
    return 0;
}

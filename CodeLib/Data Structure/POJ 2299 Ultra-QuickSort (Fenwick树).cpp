/*
** POJ 2299 Ultra-QuickSort
** Created by Rayn @@ 2014/04/08
** 用树状数组来计算逆序数
** 0 ≤ a[i] ≤ 999999999，数据太大了
** 先要学会让数据离散化
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAX = 500010;

struct item{
    int id, val;
    bool operator < (const item &a) const {
        return val < a.val;
    }
};
item arr[MAX];
int n, b[MAX], tree[MAX];

inline int lowbit(int idx)
{
    return idx & (-idx);
}
void Update(int idx, int val)
{
    while(idx <= MAX)
    {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}
LL ReadSum(int idx)
{
    LL sum = 0;
    while(idx > 0)
    {
        sum += tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}
int main()
{
    int n;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i=1; i<=n; ++i)
        {
            scanf("%d", &arr[i].val);
            arr[i].id = i;
        }
        sort(arr+1, arr+n+1);
        for(int i=1; i<=n; ++i)
            b[arr[i].id] = i;
        memset(tree, 0, sizeof(tree));

        LL ans = 0;
        for(int i=1; i<=n; ++i)
        {
            Update(b[i], 1);
            ans += i - ReadSum(b[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

/*
** POJ 3928 Ping pong
** Created by Rayn @@ 2014/04/07
** Ê÷×´Êý×é(Binary Indexed Trees)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAX = 20010;
const int MaxA = 100010;

int MaxVal, tree[MaxA];
int arr[MAX], c[MAX], d[MAX];

inline int lowbit(int idx)
{
    return idx&(-idx);
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
    while(idx <= MaxVal)
    {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}
int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);

        MaxVal = -1;
        for(int i=1; i<=n; ++i)
        {
            scanf("%d", &arr[i]);
            MaxVal = max(MaxVal, arr[i]);
        }

        memset(tree, 0, sizeof(tree));
        for(int i=1; i<=n; ++i)
        {
            Update(arr[i], 1);
            c[i] = ReadSum(arr[i]-1);
        }

        memset(tree, 0, sizeof(tree));
        for(int i=n; i>=1; --i)
        {
            Update(arr[i], 1);
            d[i] = ReadSum(arr[i]-1);
        }
        LL ans = 0;
        for(int i=1; i<=n; ++i)
        {
            ans += (LL)c[i]*(n-i-d[i]) + (LL)d[i]*(i-c[i]-1);
        }
        printf("%lld\n", ans);

    }
	return 0;
}

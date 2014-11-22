/*
** HDU 1556 Color the Ball
** Created by Rayn @@ 2014/08/17
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 100010;

int n;
int tree[MAXN];

inline int Lowbit(int x)
{
    return x & (-x);
}
void Add(int x, int val)
{
    while(x <= n)
    {
        tree[x] += val;
        x += Lowbit(x);
    }
}
int getSum(int x)
{
    int ret = 0;
    while(x > 0)
    {
        ret += tree[x];
        x -= Lowbit(x);
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) != EOF && n)
    {
        memset(tree, 0, sizeof(tree));
        for(int i = 1; i <= n; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            Add(a, 1);
            Add(b+1, -1);
        }
        for(int i = 1; i <= n; ++i)
        {
            printf("%d%c", getSum(i), (i == n ? '\n':' '));
        }
    }
    return 0;
}

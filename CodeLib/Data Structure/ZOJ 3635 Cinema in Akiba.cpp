/*
** ZOJ 3635 Cinema in Akiba
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 50010;

int n;
int tree[MAXN];
int pos[MAXN];

int LowBit(int x)
{
    return x&(-x);
}
void Add(int x, int v)
{
    while(x <= n)
    {
        tree[x] += v;
        x += LowBit(x);
    }
}
int getSum(int x)
{
    int res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= LowBit(x);
    }
    return res;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int m, q;
    while(scanf("%d", &n) != EOF)
    {
        memset(tree, 0, sizeof(tree));
        for(int i = 1; i <= n; ++i)
        {
            Add(i, 1);
        }
        for(int i = 1, ai; i <= n; ++i)
        {
            scanf("%d", &ai);
            int l = 1, r = n;
            while(l < r)
            {
                int mid = (l + r) >> 1;
                if(getSum(mid) >= ai)
                    r = mid;
                else
                    l = mid+1;
            }
            pos[i] = l;
            Add(l, -1);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d", &q);
            printf("%d%c", pos[q], (i == m-1)?'\n':' ');
        }
    }
    return 0;
}

/*
** POJ 3067 Japan
** Created by Rayn @@ 2014/04/09
** Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
using namespace std;
const int MAX = 1010;

struct pos{
    int E, W;
    bool operator < (const pos &a) const {
        return E > a.E || (E == a.E && W > a.W);
    }
};
pos way[MAX*MAX];
int tree[MAX];

inline int lowbit(int idx)
{
    return idx & (-idx);
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
    int T, n, m, k, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &k);
        for(int i=1; i<=k; ++i)
        {
            scanf("%d%d", &way[i].E, &way[i].W);
        }
        sort(way+1, way+k+1);
        memset(tree, 0, sizeof(tree));
        LL cnt = 0;
        for(int i=1; i<=k; ++i)
        {
            cnt += ReadSum(way[i].W - 1);
            //printf("%d\n",cnt);
            Update(way[i].W, 1);
        }
        printf("Test case %d: %lld\n", ++cases, cnt);
    }
    return 0;
}

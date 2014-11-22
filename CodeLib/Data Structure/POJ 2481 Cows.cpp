/*
** POJ 2481 Cows
** Created by Rayn @@ 2014/04/09
** Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 100010;

struct pos{
    int S, E;
    int id;
    bool operator < (const pos &a) const {
        return E > a.E || (E == a.E && S < a.S);
    }
};
pos cow[MAX];
int tree[MAX], ans[MAX];

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
    int n;
    while(scanf("%d", &n) != EOF && n)
    {
        for(int i=1; i<=n; ++i)
        {
            scanf("%d%d", &cow[i].S, &cow[i].E);
            cow[i].S++;
            cow[i].E++;
            cow[i].id = i;
        }
        sort(cow+1, cow+n+1);
        memset(tree, 0, sizeof(tree));
        memset(ans, 0, sizeof(ans));
        int cnt = 0;
        for(int i=1; i<=n; ++i)
        {
            if(i>1 && cow[i].S==cow[i-1].S && cow[i].E==cow[i-1].E)
                ans[cow[i].id] = ans[cow[i-1].id];
            else
                ans[cow[i].id] = ReadSum(cow[i].S);
            Update(cow[i].S, 1);
        }
        for(int i=1; i<=n; ++i)
        {
            printf("%d%c", ans[i], (i == n)? '\n' : ' ');
        }

    }
    return 0;
}

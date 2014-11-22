/*
** POJ 1195 Mobile phones
** Created by Rayn @@ 2014/04/10
** ¶þÎ¬Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1030;

int tree[MAX][MAX];

inline int lowbit(int x)
{
    return x & (-x);
}
int GetSum(int x, int y)
{
    int sum = 0;
    while(x > 0)
    {
        int ty = y;
        while(ty > 0)
        {
            sum += tree[x][ty];
            ty -= lowbit(ty);
        }
        x -= lowbit(x);
    }
    return sum;
}
void Update(int x, int y, int val)
{
    while(x <= MAX)
    {
        int ty = y;
        while(ty <= MAX)
        {
            tree[x][ty] += val;
            ty += lowbit(ty);
        }
        x += lowbit(x);
    }
}
int main()
{
    int cmd, s;
    int x, y, a;
    int l, b, r, t;

    while(scanf("%d", &cmd) != EOF)
    {
        if(cmd == 0)
        {
            scanf("%d", &s);
            memset(tree, 0, sizeof(tree));
        }
        else if(cmd == 1)
        {
            scanf("%d%d%d", &x, &y, &a);
            Update(x+1, y+1, a);
        }
        else if(cmd == 2)
        {
            scanf("%d%d%d%d",&l, &b, &r, &t);
            int ans = GetSum(r+1,t+1) - GetSum(r+1,b) - GetSum(l,t+1) + GetSum(l,b);
            printf("%d\n", ans);
        }
        else if(cmd == 3)
        {
            break;
        }
    }
    return 0;
}

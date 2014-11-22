/*
** HDU 1166 µÐ±ø²¼Õó
** Created by Rayn @@ 2014/04/11
** Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 50010;
int tree[MAX];
int N;

inline int lowbit(int x)
{
    return x & (-x);
}
void Update(int x, int val)
{
    while(x <= N)
    {
        tree[x] += val;
        x += lowbit(x);
    }
}
int GetSum(int x)
{
    int sum = 0;
    while(x > 0)
    {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
int main()
{
    int T, x, y, cases = 0;

    scanf("%d", &T);
    while(T--)
    {
        memset(tree, 0, sizeof(tree));
        scanf("%d", &N);
        for(int i=1; i<=N; ++i)
        {
            scanf("%d", &x);
            Update(i, x);
        }
        printf("Case %d:\n", ++cases);
        char op[10];
        while(scanf("%s", op) && op[0] != 'E')
        {
            scanf("%d%d", &x, &y);
            if(op[0] == 'A')
            {
                Update(x, y);
            }
            else if(op[0] == 'S')
            {
                Update(x, -y);
            }
            else if(op[0] == 'Q')
            {
                printf("%d\n", GetSum(y)-GetSum(x-1));
            }
        }
    }
    return 0;
}

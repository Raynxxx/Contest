/*
** ZOJ 3789 Gears
** Created by Rayn @@ 2014/07/09
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 600000+10;

int n, m, cnt;
int id[MAXN], pa[MAXN];
int num[MAXN], rnk[MAXN];

void Init(int n)
{
    cnt = n;
    for(int i = 1; i <= n; ++i)
    {
        pa[i] = id[i] = i;
        rnk[i] = 0;
        num[i] = 1;
    }
}
int FindSet(int x)
{
    if(x != pa[x])
    {
        int root = pa[x];
        pa[x] = FindSet(pa[x]);
        rnk[x] = (rnk[x] + rnk[root]) % 2;
    }
    return pa[x];
}
void UnionSet(int x, int y)
{
    int px = FindSet(x);
    int py = FindSet(y);
    if(px != py)
    {
        pa[px] = py;
        num[py] += num[px];
        rnk[px] = (rnk[x] + rnk[y] + 1) % 2;
    }
}
void Del(int x)
{
    int px = FindSet(id[x]);
    num[px]--;
    id[x] = ++cnt;
    pa[id[x]] = id[x];
    num[id[x]] = 1;
    rnk[id[x]] = 0;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char op[5];
    int x, y;

    while(scanf("%d%d%*c", &n, &m) != EOF)
    {
        Init(n);
        while(m--)
        {
            scanf("%s", op);
            if(op[0] == 'L')
            {
                scanf("%d%d", &x, &y);
                UnionSet(id[x], id[y]);
            }
            else if(op[0] == 'D')
            {
                scanf("%d", &x);
                Del(x);
            }
            else if(op[0] == 'Q')
            {
                scanf("%d%d", &x, &y);
                int px = FindSet(id[x]);
                int py = FindSet(id[y]);
                if(px != py)
                {
                    printf("Unknown\n");
                }
                else if((rnk[id[x]]&1) == (rnk[id[y]]&1))
                {
                    printf("Same\n");
                }
                else
                {
                    printf("Different\n");
                }
            }
            else if(op[0] == 'S')
            {
                scanf("%d", &x);
                int px = FindSet(id[x]);
                printf("%d\n", num[px]);
            }
        }
        /*
        puts("");
        for(int i = 1; i < cnt; ++i)
        {
            printf("rnk[%d]: %d\n", i, rnk[i]);
        }
        puts("");
        */
    }
    return 0;
}

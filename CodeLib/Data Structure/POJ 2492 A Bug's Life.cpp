/*
** POJ 1611 The Suspects
** Created by Rayn @@ 2014/04/06
** 加权的并查集
*/
#include <cstdio>
#include <cstring>

const int MAX = 2010;
int pa[MAX];
int rnk[MAX];   //记录与父节点的关系，0同类，1异类

int FindSet(int x)
{
    if(x != pa[x])
    {
        int root = pa[x];
        pa[x] = FindSet(pa[x]);
        rnk[x] = (rnk[x] + rnk[root]) % 2;  //每次回溯更新一次父节点，相应更新关系
    }
    return pa[x];
}
void Init(int n)
{
    memset(rnk, 0, sizeof(rnk));
    for(int i=0; i<=n; ++i)
        pa[i] = i;
}
int main()
{
    int n, cases = 0;

    scanf("%d", &n);
    while(n--)
    {
        int bug, inter;

        scanf("%d%d", &bug, &inter);
        Init(bug);

        int flag = 1, x, y;
        while(inter--)
        {
            scanf("%d%d", &x, &y);
            int tx = FindSet(x);
            int ty = FindSet(y);
            if(tx != ty)
            {
                pa[tx] = ty;
                rnk[tx] = (rnk[x] + 1 + rnk[y]) % 2;
            }
            else
            {
                if(rnk[x] == rnk[y])
                    flag = 0;
            }
        }
        printf("Scenario #%d:\n", ++cases);
        if(flag)
            printf("No suspicious bugs found!\n\n");
        else
            printf("Suspicious bugs found!\n\n");
    }
    return 0;
}

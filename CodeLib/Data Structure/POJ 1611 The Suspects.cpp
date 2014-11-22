/*
** POJ 1611 The Suspects
** Created by Rayn @@ 2014/04/06
** 并查集,样例数据太水了，开始写的搓也没出错
*/
#include <cstdio>

const int MAX = 30010;
int pa[MAX];

int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
    int n, m;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0)
            break;

        for(int i=0; i<n; ++i)
            pa[i] = i;

        int k, x, y;
        while(m--)
        {
            scanf("%d %d", &k, &x); //这里应该是判断和第一个学生的集合关系
            int px = FindSet(x);    //x的值会改变，用另外的变量存
            for(int i=1; i<k; ++i)
            {
                scanf("%d", &y);
                int py = FindSet(y);
                if(px != py)
                    pa[py] = px;
            }
        }
        int ans = 0, sign = FindSet(0);
        for(int i=0; i<n; ++i)
        {
            if(FindSet(i) == sign)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}

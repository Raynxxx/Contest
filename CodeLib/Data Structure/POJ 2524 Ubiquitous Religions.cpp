/*
** POJ 2524 Ubiquitous Religions
** Created by Rayn @@ 2014/04/06
** 简单并查集，水题
*/
#include <cstdio>
using namespace std;

const int MAX = 50010;
int pa[MAX];

int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
    int n, m, cases = 0;

    while(scanf("%d%d", &n, &m) != EOF && n && m)
    {
        for(int i=1; i<=n; ++i)
            pa[i] = i;

        int x, y;
        while(m--)
        {
            scanf("%d %d", &x, &y);
            x = FindSet(x);
            y = FindSet(y);
            if(x != y)
                pa[x] = y;
        }
        int cnt = 0;
        for(int i=1; i<=n; ++i)
        {
            if(i == pa[i])
                cnt++;
        }
        printf("Case %d: %d\n", ++cases, cnt);
    }
}

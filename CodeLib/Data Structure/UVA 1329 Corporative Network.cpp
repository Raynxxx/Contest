/*
** UVA 1329 Corporative Network
** Created by Rayn @@ 2014/04/04
** ²¢²é¼¯
*/
#include <cstdio>

const int MAX = 20010;
int pa[MAX], d[MAX];

int FindSet(int x)
{
    if(x != pa[x])
    {
        int root = FindSet(pa[x]);
        d[x] += d[pa[x]];
        pa[x] = root;
        return root;
    }
    else
        return x;
}
int Abs(int x)
{
    return (x < 0)? -x : x;
}
int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, u, v;
        char order[5];

        scanf("%d", &n);
        for(int i=0; i<n; ++i)
        {
            pa[i] = i;
            d[i] = 0;
        }
        while(scanf("%s", &order) && order[0] != 'O')
        {
            if(order[0] == 'E')
            {
                scanf("%d", &u);
                FindSet(u);
                printf("%d\n", d[u]);
            }
            if(order[0] == 'I')
            {
                scanf("%d%d", &u, &v);
                pa[u] = v;
                d[u] = Abs(u-v) % 1000;
            }
        }
    }
    return 0;
}

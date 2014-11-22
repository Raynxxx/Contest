/*
** POJ 1182 食物链
** Created by Rayn @@ 2014/04/11
** 加权并查集
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX = 50010;
int pa[MAX], rnk[MAX];

int Find(int x)
{
    if(x != pa[x])
    {
        int root = pa[x];
        pa[x] = Find(pa[x]);
        rnk[x] = (rnk[x] + rnk[root]) % 3;
    }
    return pa[x];
}
int main()
{
    int N, K, d, x, y;

    scanf("%d%d", &N, &K);

    int error = 0;
    for(int i=0; i<=N; ++i)
    {
        pa[i] = i;
        rnk[i] = 0;
    }
    for(int i=0; i<K; ++i)
    {
        scanf("%d%d%d", &d, &x, &y);
        if(x>N || y>N || (d==2 && x==y))
        {
            error++;
            continue;
        }
        int px = Find(x);
        int py = Find(y);
        if(px == py)
        {
            if(d == 1 && rnk[x] != rnk[y])
                error++;
            if(d == 2 && (rnk[x]+1)%3 != rnk[y])
                error++;
        }
        else
        {
            pa[py] = px;
            rnk[py] = (3-rnk[y]+rnk[x]+(d-1)) % 3;
        }
    }
    printf("%d\n", error);

    return 0;
}

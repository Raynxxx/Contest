/*
** HDU 1213 How Many Tables
** Created by Rayn @@ 2014/04/27
** 简单并查集啊，一开始把初始化写在了
** N,M读入数值之前，总是错，脑壳真是有屎啊
*/
#include <cstdio>
#include <cstring>
const int MAX = 1010;

int T, N, M;
int pa[MAX];

void Init()
{
    for(int i=1; i<=N; ++i)
        pa[i] = i;
}
inline int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
    int x, y;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &M);

        Init();
        while(M--)
        {
            scanf("%d%d", &x, &y);
            int tx = FindSet(x);
            int ty = FindSet(y);
            if(tx != ty)
                pa[ty] = tx;
        }
        int ans = 0;
        for(int i=1; i<=N; ++i)
        {
            if(i == FindSet(i))
                ans++;
        }
        printf("%d\n", ans);
        //if(T > 0) 被样例给误导了啊
            //printf("\n");
    }
    return 0;
}

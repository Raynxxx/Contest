/*
** HDU 1856 More is better
** Created by Rayn @@ 2014/04/28
** ²¢²é¼¯
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 10000005;

int N;
int pa[MAX], num[MAX];

void Init()
{
    for(int i=1; i<MAX; ++i)
    {
        pa[i] = i;
        num[i] = 1;
    }
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

    while(scanf("%d", &N) != EOF)
    {
        if(N == 0)
        {
            printf("1\n");
            continue;
        }
        Init();
        int cnt = 0;
        for(int i=0; i<N; ++i)
        {
            scanf("%d%d", &x, &y);
            cnt = max(cnt, x);
            cnt = max(cnt, y);
            int px = FindSet(x);
            int py = FindSet(y);
            if(px != py)
            {
                pa[px] = py;
                num[py] += num[px];
            }
        }
        //printf("%d\n", cnt);
        int ans = -1;
        for(int i=1; i<=cnt; ++i)
        {
            if(num[i] > ans)
                ans = num[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}

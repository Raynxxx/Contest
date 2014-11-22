/*
** UVA 1160 X-Plosives
** Created by Rayn @@ 2014/04/04
** ²¢²é¼¯
*/
#include <cstdio>

const int MAX = 100010;
int arr[MAX];

int FindSet(int x)
{
    return (arr[x] != x) ? arr[x] = FindSet(arr[x]) : x;
}
int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int x, y;

    while(scanf("%d", &x) == 1)
    {
        for(int i=0; i<MAX; ++i)
            arr[i] = i;

        int refu = 0;
        while(x != -1)
        {
            scanf("%d", &y);
            x = FindSet(x);
            y = FindSet(y);
            if(x == y)
                ++refu;
            else
                arr[x] = y;
            scanf("%d", &x);
        }
        printf("%d\n", refu);
    }
    return 0;
}

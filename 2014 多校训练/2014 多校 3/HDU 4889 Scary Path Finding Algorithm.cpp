/*
** HDU 4889 Scary Path Finding Algorithm
** Created by Rayn @@ 2014/08/18
*/
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int C, f[33];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    f[0] = -1;
    for(int i = 1; i <= 30; i++)
        f[i] = f[i-1] * 2;
    while(scanf("%d", &C) != EOF)
    {
        puts("99 87");
        for(int i = 1; i < 30; i++)
        {
            printf("%d %d 0\n", i, i+30);
            printf("%d %d %d\n", i, i+1, f[29-i]);
            printf("%d %d %d\n", i+30, i+1, f[30-i]);
        }
    }
    return 0;
}

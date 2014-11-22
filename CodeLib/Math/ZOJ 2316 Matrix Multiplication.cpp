/*
** ZOJ 2316 Matrix Multiplication
** Created by Rayn @@ 2014/08/10
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int a[10001];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int t, n, m;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            a[u]++;
            a[v]++;
        }
        int res = 0;
        for(int i = 1; i <= n; ++i)
        {
            res += a[i]*a[i];
        }
        printf("%d\n", res);
        if(t > 0)
            printf("\n");
    }
    return 0;
}

/*
** CodeForces 447A DZY Loves Hash
** Created by Rayn @@ 2014/07/13
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 310;

bool Hash[MAXN];
int arr[MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, p;

    while(scanf("%d%d", &p, &n) != EOF)
    {
        memset(Hash, false, sizeof(Hash));
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &arr[i]);
        }
        bool flag = true;
        for(int i = 0; i < n; ++i)
        {
            int x = arr[i] % p;
            if(Hash[x])
            {
                printf("%d\n", i+1);
                flag = false;
                break;
            }
            Hash[x] = true;
        }
        if(flag)
            printf("-1\n");
    }
    return 0;
}

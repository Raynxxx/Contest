/*
** HDU 4861 Couple doubi
** Created by Rayn @@ 2014/08/16
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
typedef long long LL;
using namespace std;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int k, p;

    while(scanf("%d%d", &k, &p) != EOF)
    {
        int flag = k / (p-1);
        if(flag & 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

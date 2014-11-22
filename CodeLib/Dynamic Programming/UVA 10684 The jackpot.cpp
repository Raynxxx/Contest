/*
** UVA 10684 The jackpot
** Created by Rayn @@ 2014/05/05
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 10010;

int main()
{
    int n, a, sum, ans;

    while(scanf("%d", &n) != EOF && n)
    {
        sum = ans = 0;
        for(int i=0; i<n; ++i)
        {
            scanf("%d", &a);
            if(sum < 0)
                sum = a;
            else
                sum += a;
            ans = max(ans, sum);
        }
        if(ans > 0)
            printf("The maximum winning streak is %d.\n", ans);
        else
            printf("Losing streak.\n");
    }
    return 0;
}

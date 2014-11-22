/*
** ZOJ 3464 Rugby Football
** Created by Rayn @@ 2014/08/11
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int v[10007];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases;
    int n, t, l;
    scanf("%d", &cases);
    while (cases--)
    {
        scanf("%d%d%d", &n, &t, &l);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &v[i]);
        }
        sort(v, v+n);
        double ans = 0.0;
        for (int i = n-1; i >= 0; --i) {
            if (t * v[i] <= l) {
                ans += t;
                l -= t * v[i];
            } else {
                ans += 1.0 * l / v[i];
                l = 0;
                break;
            }
        }
        if (l == 0) {
            printf("%.2f\n", ans);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}

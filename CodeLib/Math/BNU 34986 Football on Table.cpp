/*
** BNU 34986 Football on Table
** Created by Rayn @@ 2014/06/03
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 210;

double w[MAX], d[MAX];
double sumw[MAX], sumd[MAX];

int main()
{
    int t, m, cases = 0;

    scanf("%d", &t);
    while(t--)
    {
        double L, W;
        double x0, y0, dx, dy;
        scanf("%lf%lf", &L, &W);
        scanf("%lf%lf%lf%lf", &x0, &y0, &dx, &dy);
        scanf("%d", &m);

        double ans = 1.0, x;
        while(m--)
        {
            int n;
            scanf("%lf%d",&x,&n);
            for(int i = 1; i <= n; i++)
                scanf("%lf", &w[i]);
            for(int i = 1; i < n; i++)
                scanf("%lf", &d[i]);
            if(x <= x0)
                continue;
            double y = y0 + (x - x0)*dy/dx;
            sumw[0] = sumd[0] = 0.0;
            for(int i = 1; i <= n; i++)
                sumw[i] = sumw[i-1] + w[i];
            for(int i = 1; i < n; i++)
                sumd[i] = sumd[i-1] + d[i];

            double cango = W - sumw[n] - sumd[n-1];
            double go = 0.0;
            for(int i = 0; i <= n; i++)
            {
                double up, down;
                if(i == 0)
                {
                    down = y;
                    up = cango;
                }
                else if(i == n)
                {
                    down = 0.0;
                    up = y - sumw[n] - sumd[n-1];
                }
                else
                {
                    down = max(0.0, y-sumw[i]-sumd[i]);
                    up = min(cango, y-sumw[i]-sumd[i-1]);
                }
                if(up > down)
                    go += up - down;
            }
            ans *= go / cango;
        }
        printf("Case #%d: %.5f\n", ++cases, ans);
    }
    return 0;
}

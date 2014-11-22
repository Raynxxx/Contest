/*
** POJ 2318 TOYS
** Created by Rayn @@ 2014/05/04
** 一个矩形，有被若干直线分成N个格子，给出一个点的坐
** 标，问你该点位于哪个点中。其实就是点在凸四边形内
** 的判断，若利用叉积的性质，可以二分求解。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 5010;
const int INF = 0x3f3f3f3f;

struct Point {
    double x, y;
    Point(double a=0, double b=0): x(a), y(b) {}
} dot[MAX];

double up[MAX], low[MAX];
int ans[MAX];

double Cross(Point A, Point B, Point C)
{
    return (C.x-A.x)*(B.y-A.y)-(B.x-A.x)*(C.y-A.y);
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int n, m, first = 1;
    double x1, y1, x2, y2;

    while(scanf("%d", &n) != EOF && n)
    {
        if(!first)
            printf("\n");
        first = 0;

        scanf("%d%lf%lf%lf%lf", &m, &x1, &y1, &x2, &y2);
        for(int i=0; i<n; ++i)
        {
            scanf("%lf%lf", &up[i], &low[i]);
        }
        up[n] = low[n] = x2; //最后一条，矩形的右边(x2,y1),(x2,y2)，方便判断;

        //强大的二分
        memset(ans, 0, sizeof(ans));
        for(int i=0; i<m; ++i)
        {
            scanf("%lf%lf", &dot[i].x, &dot[i].y);
            int left = 0, right = n, mid = 0;
            while(left <= right)
            {
                mid = (left + right) / 2;
                Point b(low[mid], y2), c(up[mid], y1);
                if(Cross(dot[i], b, c) > 0)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            ans[left]++;
        }
        for(int i=0; i<=n; ++i)
            printf("%d: %d\n", i, ans[i]);
    }
    return 0;
}

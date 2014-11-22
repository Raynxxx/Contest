/*
** POJ 2398 Toy Storage
** Created by Rayn @@ 2014/05/05
** 一个矩形，有被若干直线分成N个格子，给出一个点的坐
** 标，问你该点位于哪个点中。其实就是点在凸四边形内
** 的判断，若利用叉积的性质，可以二分求解。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1010;
const int INF = 0x3f3f3f3f;

struct Point {
    double x, y;
    Point(double a=0, double b=0): x(a), y(b) {}
} dot[MAX];

struct Line {
    double up, low;
    bool operator < (const Line& rhs) const {
        double x1 = min(up, low);
        double x2 = min(rhs.up, rhs.low);
        if(x1 == x2)
            return max(up, low) < max(rhs.up, rhs.low);
        else
            return x1 < x2;
    }
} line[MAX];

int num[MAX], ans[MAX];

double Cross(Point A, Point B, Point C)
{
    return (B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y);
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int n, m;
    double x1, y1, x2, y2;

    while(scanf("%d", &n) != EOF && n)
    {

        scanf("%d%lf%lf%lf%lf", &m, &x1, &y1, &x2, &y2);
        //printf("%d %d\n", n, m);
        for(int i=0; i<n; ++i)
        {
            scanf("%lf%lf", &line[i].up, &line[i].low);
        }
        sort(line, line+n);
        line[n].up = line[n].low = x2;

        memset(num, 0, sizeof(num));
        memset(ans, 0, sizeof(ans));
        for(int i=0; i<m; ++i)
        {
            scanf("%lf%lf", &dot[i].x, &dot[i].y);
            int left = 0, right = n, mid = 0;
            while(left <= right)
            {
                mid = (left + right) / 2;
                Point b(line[mid].up, y1);
                Point c(line[mid].low, y2);
                if(Cross(dot[i], b, c) > 0)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            num[left]++;
        }
        for(int i=0; i<=n; ++i)
        {
            if(num[i])
                ans[num[i]]++;
        }
        printf("Box\n");
        for(int i=0; i<=n; ++i)
        {
            if(ans[i])
                printf("%d: %d\n", i, ans[i]);
        }
    }
    return 0;
}

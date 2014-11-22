/*
** POJ 2187 Beauty Contest
** Created by Rayn @@ 2014/03/31
** 凸包 + 枚举
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAX 50005
using namespace std;

struct pos{
    double x, y;
    bool operator < (const pos &a) const {
        return y < a.y || (y == a.y && x < a.x);
    };
};

int n;
pos arr[MAX], dot[MAX];

double length2(pos a, pos b)
{
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
double Cross(pos p1, pos p2, pos p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
}
int Tubao(pos *p, int n)
{
    sort(p, p+n);
    int m = 0;
    for(int i=0; i<n; ++i)
    {
        while(m > 1 && Cross(dot[m-1], dot[m-2], p[i])<=0)
            m--;
        dot[m++] = p[i];
    }
    int k = m;
    for(int i=n-2; i>=0; i--)
    {
        while(m > k && Cross(dot[m-1], dot[m-2], p[i])<=0)
            m--;
        dot[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}
int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%lf %lf", &arr[i].x, &arr[i].y);

    if(n < 3)   //3点一下无法形成凸包
    {
        printf("%.f\n", length2(arr[0],arr[1]));
        return 0;
    }

    n = Tubao(arr, n);
    /* test sort
    for(int i=0; i<n; ++i)
        printf("%.f %.f\n", arr[i].x, arr[i].y);
    for(int i=0; i<n; ++i)
        printf("%.f %.f\n", dot[i].x, dot[i].y);
    //*/
    double ans = 0;
    for(int i=0; i<n-1; ++i)
    {
        for(int j=i+1; j<n; ++j)
        {
            ans = max(ans, length2(dot[i], dot[j]));
        }
    }
    printf("%.f\n", ans);
    return 0;
}

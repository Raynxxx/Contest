/*
** POJ 1981 Circle and Points
** Created by Rayn @@ 2014/04/01
** 极角公式
** 开始没有用eps啊，总是错啊
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAX 310
#define eps 1e-10
using namespace std;

struct point{
    double x, y;
    bool operator < (const point &a) const {
        return x < a.x || (x == a.x && y < a.y);
    };
};

int n;
point arr[MAX];

double length(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int Mid(point a, point b)
{
    point mid;
    mid.x = (a.x + b.x) / 2.0;//a,b两点的中点
    mid.y = (a.y + b.y) / 2.0;

    double k = atan2(a.x-b.x, b.y-a.y);
    double len = sqrt(1 - length(a, b)*length(a, b)/4.0); //圆心到AB中点的距离
    mid.x += len * cos(k);
    mid.y += len * sin(k);

    int dot = 0;
    for(int i=0; i<n; ++i)
    {
        if(length(arr[i], mid) <= 1+eps)
            dot++;
    }
    return dot;
}
int main()
{

#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &n)!=EOF && n)
    {
        for(int i=0; i<n; ++i)
            scanf("%lf%lf", &arr[i].x, &arr[i].y);
        sort(arr, arr+n);
        /*test sort
        for(int i=0; i<n; ++i)
            printf("%.5f %.5f\n", arr[i].x, arr[i].y);
        //*/

        int ans = 1, cnt;
        for(int i=0; i<n; ++i)
        {
            for(int j=i+1; j<n && arr[j].x-arr[i].x < 2; ++j)
            {
                if(length(arr[i], arr[j]) <= 2+eps)
                {
                    ans = max(ans, Mid(arr[i],arr[j]));
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

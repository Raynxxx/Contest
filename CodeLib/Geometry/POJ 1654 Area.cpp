/*
** POJ 1654 Area
** Created by Rayn @@ 2014/06/09
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
typedef long long LL;
const int MAX = 1000010;
char str[MAX];

struct Point {
    int x, y;
    Point(int x=0, int y=0) :
        x(x), y(y) {}
} po[MAX];
typedef Point Vector;

Vector operator - (const Point& a, const Point& b) {
    return Point(a.x-b.x, a.y-b.y);
}

double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}
int main()
{
    int t;

    scanf("%d%*c", &t);
    while(t--)
    {
        gets(str);
        int len = strlen(str);
        if(len == 1)
        {
            printf("0\n");
            continue;
        }
        Point now(0, 0);
        int cnt = 0;
        for(int i = 0; i < len; ++i)
        {
            switch(str[i])
            {
                case '8':
                    now.y++;
                    po[cnt++] = now;
                    break;
                case '2':
                    now.y--;
                    po[cnt++] = now;
                    break;
                case '6':
                    now.x++;
                    po[cnt++] = now;
                    break;
                case '4':
                    now.x--;
                    po[cnt++] = now;
                    break;
                case '9':
                    now.x++; now.y++;
                    po[cnt++] = now;
                    break;
                case '7':
                    now.x--; now.y++;
                    po[cnt++] = now;
                    break;
                case '3':
                    now.x++; now.y--;
                    po[cnt++] = now;
                    break;
                case '1':
                    now.x--; now.y--;
                    po[cnt++] = now;
                    break;
                case '5':
                    cnt--;
                    break;
            }
        }
        double ans = 0.0;
        now = Point(0, 0);
        for(int i = 0; i < cnt-1; ++i)
        {
            ans += Area2(now, po[i], po[i+1]);
        }
        ans = fabs(ans);
        if((LL)ans % 2 == 0)
            printf("%lld\n", (LL)ans/2);
        else
            printf("%lld.5\n", (LL)ans/2);
    }
    return 0;
}

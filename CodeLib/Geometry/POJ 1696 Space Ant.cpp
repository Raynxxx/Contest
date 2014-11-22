/*
** POJ 1696 Space Ant
** Created by Rayn @@ 2014/05/30
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 60;

struct Point {
    int id, x, y;
    Point(int id=0, int x=0, int y=0) :
        id(id), x(x), y(y) {}
    Point operator - (const Point& a) {
        return Point(id, x-a.x, y-a.y);
    }
};
typedef Point Vector;

Point plant[MAX], Start;

int Dis2(Point A, Point B)
{
    return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}
int Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
bool cmp1(const Point& a, const Point& b)
{
    return a.y < b.y;
}
bool cmp2(Point a, Point b)
{
    int ret = Cross(a-Start, b-Start);
    if(ret > 0)
        return true;
    else if(ret < 0)
        return false;
    return Dis2(Start, a) > Dis2(Start, b);
}
void Solve(Point p[], int n)
{
    sort(p, p+n, cmp1);
    printf("%d %d", n, p[0].id);
    Start = p[0];
    for(int i = 1; i < n; ++i)
    {
        sort(p+i, p+n, cmp2);
        printf(" %d", p[i].id);
        Start = p[i];
    }
    printf("\n");
}
int main()
{
    int m, n, id, x, y;

    scanf("%d", &m);
    while(m--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &id, &x, &y);
            plant[i] = Point(id, x, y);
        }
        Solve(plant, n);
    }
    return 0;
}

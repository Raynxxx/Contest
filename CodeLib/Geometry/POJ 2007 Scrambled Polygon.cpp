/*
** POJ 2007 Scrambled Polygon
** Created by Rayn @@ 2014/06/03
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 60;

struct Point {
    int x, y;
    Point(int x=0, int y=0) :
        x(x), y(y) {}
    Point operator - (const Point& rhs) {
        return Point(x-rhs.x, y-rhs.y);
    }
} po[MAX];

int Cross(Point A, Point B)
{
    return A.x*B.y - A.y*B.x;
}
bool cmp(const Point& a, const Point& b)
{
    return Cross(a, b) > 0;
}
int main()
{
    int n = 0;
    while(scanf("%d%d", &po[n].x, &po[n].y) != EOF)
    {
        if(po[n].x == 0 && po[n].y == 0)
            swap(po[n], po[0]);
        n++;
    }

    sort(po+1, po+n, cmp);
    for(int i = 0; i < n; ++i)
    {
        printf("(%d,%d)\n", po[i].x, po[i].y);
    }
    return 0;
}

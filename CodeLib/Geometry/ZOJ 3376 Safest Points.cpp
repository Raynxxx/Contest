/*
** ZOJ 3376 Safest Points
** Created by Rayn @@ 2014/06/01
*/
#include <cstdio>
#include <queue>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 1010;
const int INF = 0x7FFFFFFF;

int dis[MAX][MAX];
int dir[][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};
int w, h, n;
bool rx, ry, rxy;

int GCD(int m, int n)
{
    return (n == 0) ? m : GCD(n, m%n);
}
/* 取整，整数即向上取整，负数向下 */
int Floor(int a, int b)
{
    if(a < 0)
        return -((-a + b - 1) / b);
    else
        return a / b;
}
void Mark(int x, int y)
{
    if(rxy)
        swap(x, y);
    if(ry)
        y = -y;
    if(rx)
        x = -x;
    if(x >= 0 && x < w && y >= 0 && y < h)
        dis[x][y] = 0;
}
/* 把射线边上的点编辑为危险点 */
void Solve(int w, int h, int x, int y, int dx, int dy)
{
    if((rx = (dx < 0)))
    {
        w = -w; x = -x; dx = -dx;
    }
    if((ry = (dy < 0)))
    {
        h = -h; y = -y; dy = -dy;
    }
    if((rxy = (dx < dy)))
    {
        swap(w, h); swap(x, y); swap(dx, dy);
    }
    int g = GCD(dx, dy);
    dx /= g; dy /= g;
    for(int i = x; i < w || i <= 0; ++i)
    {
        int j = Floor(y*dx + (i-x)*dy, dx);
        if((i - x) % dx != 0)
            Mark(i, j+1);
        Mark(i, j);
    }
}
int main()
{
    int x, y, dx, dy;

    while(scanf("%d%d%d", &w, &h, &n) != EOF)
    {
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0; j < h; ++j)
            {
                dis[i][j] = -1;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d%d", &x, &y, &dx, &dy);
            Solve(w, h, x, y, dx, dy);
        }
        int maxd = 0;
        queue<pair<int, int> > q;
        for(int i = 0; i < w; ++i)
        {
            for(int j = 0; j < h; ++j)
            {
                if(dis[i][j] == 0)
                    q.push(make_pair(i, j));
            }
        }
        while(!q.empty())
        {
            x = q.front().first;
            y = q.front().second;
            q.pop();
            for(int i = 0; i < 4; ++i)
            {
                dx = x + dir[i][0];
                dy = y + dir[i][1];
                if(dx >= 0 && dx < w && dy >= 0 && dy < h && dis[dx][dy] == -1)
                {
                    dis[dx][dy] = dis[x][y] + 1;
                    if(dis[dx][dy] > maxd)
                        maxd = dis[dx][dy];
                    q.push(make_pair(dx, dy));
                }
            }
        }
        if(maxd == 0)
        {
            puts("MISS!");
        }
        else
        {
            bool blank = false;
            for(int i = 0; i < w; ++i)
            {
                for(int j = 0; j < h; ++j)
                {
                    if(dis[i][j] == maxd)
                    {
                        if(blank)
                            printf(" ");
                        else
                            blank = true;
                        printf("(%d, %d)", i, j);
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}

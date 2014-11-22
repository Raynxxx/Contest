/*
** POJ 2688 Cleaning Robot
** Created by Rayn @@ 2014/05/07
** 好久没做搜索，又写错了dir方向数组
** 竖向是x坐标，横向是y坐标
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 15;

int dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};/* N,S,E,W */
int loop, step;
int maze[MAX][MAX], vis[MAX][MAX];

void Init()
{
    memset(vis, 0, sizeof(vis));
    for(int i=0; i<MAX; ++i)
    {
        for(int j=0; j<MAX; ++j)
        {
            maze[i][j] = 5; //在地图外圈置为5，方便判断出界
        }
    }
}
int Trans(char ch)
{
    int dir = 5;
    switch(ch)
    {
        case 'N':
            return 0;
        case 'S':
            return 1;
        case 'E':
            return 2;
        case 'W':
            return 3;
        default:
            break;
    }
    return dir;
}
void DFS(int x, int y, int s)
{
    if(maze[x][y] == 5)
    {
        step = s;
        loop = -1;
        return ;
    }
    if(vis[x][y] != 0)
    {
        step = vis[x][y] - 1;
        loop = s - step;
        return ;
    }
    vis[x][y] = s + 1;
    int tx = x + dir[maze[x][y]][0];
    int ty = y + dir[maze[x][y]][1];
    DFS(tx, ty, vis[x][y]);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r",stdin);
#endif

    int h, w, start;
    char tmp[15];

    while(scanf("%d%d%d", &h, &w, &start) != EOF)
    {
        if(h==0 && w==0 && start==0)
            break;
        Init();
        for(int i=1; i<=h; ++i)
        {
            scanf("%s", tmp);
            for(int j=0; j<w; ++j)
            {
                maze[i][j+1] = Trans(tmp[j]);
            }
        }
        loop = 0;
        DFS(1, start, 0);
        if(loop == -1)
            printf("%d step(s) to exit\n", step);
        else
            printf("%d step(s) before a loop of %d step(s)\n", step, loop);
    }
    return 0;
}

/*
** POJ 3083 Children of the Candy Corn
** Created by Rayn @@ 2014/05/09
** 这道题重点是left和right的DFS的方向问题，方向还和游客
** 当时朝向有关，BFS就是很普通的最短路搜索
** left搜索要遵循左上右下的顺时针搜索顺序
** right搜索要遵循右上左下的逆时针搜索顺序
** 朝向标记 ：左0 上1 右2 下3
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAX = 50;
struct pos{
    int x, y;
    int step;
};
int left, right;
int w, h, sign[MAX][MAX];
char maze[MAX][MAX];
int dir[][2] = {{-1,0},{0,1},{1,0},{0,-1}}; /*0-上,1-右,2-下,3-左*/

void leftDFS(int x, int y, int face)
{
    int to[4] = {3,0,1,2};

    if(maze[x][y] == 'E')
    {
        printf("%d ", left);
        return ;
    }
    left++;
    for(int i=0; i<4; ++i)
    {
        int nowface = (face + to[i]) % 4;
        int tx = x + dir[nowface][0];
        int ty = y + dir[nowface][1];
        if(tx>=0 && ty>=0 && tx<h && ty<w && maze[tx][ty] != '#')
        {
            leftDFS(tx, ty, nowface);
            return ;
        }
    }
}
void rightDFS(int x, int y, int face)
{
    int to[4] = {1,0,3,2};

    if(maze[x][y] == 'E')
    {
        printf("%d ", right);
        return ;
    }
    right++;
    for(int i=0; i<4; ++i)
    {
        int nowface = (face + to[i]) % 4;
        int tx = x + dir[nowface][0];
        int ty = y + dir[nowface][1];
        if(tx>=0 && ty>=0 && tx<h && ty<w && maze[tx][ty] != '#')
        {
            rightDFS(tx, ty, nowface);
            return ;
        }
    }
}
void BFS(int x, int y)
{
    queue<pos> q;
    while(!q.empty())
        q.pop();

    pos start;
    start.x = x; start.y = y; start.step = 1;
    q.push(start);
    sign[x][y] = 1;

    while(!q.empty())
    {
        pos now = q.front();
        if(maze[now.x][now.y] == 'E')
        {
            printf("%d\n", now.step);
            return ;
        }
        q.pop();
        for(int i=0; i<4; ++i)
        {
            pos tmp = now;
            tmp.x = now.x + dir[i][0];
            tmp.y = now.y + dir[i][1];
            tmp.step = now.step + 1;
            if(tmp.x>=0 && tmp.y>=0 && tmp.x<h && tmp.y<w && maze[tmp.x][tmp.y] != '#' && !sign[tmp.x][tmp.y])
            {
                sign[tmp.x][tmp.y] = 1;
                q.push(tmp);
            }
        }
    }
}
int main()
{
    int cases;
    int sx, sy, face;

    scanf("%d", &cases);
    while(cases--)
    {
        memset(sign, 0, sizeof(sign));

        scanf("%d%d%*c", &w, &h);
        for(int i=0; i<h; ++i)
        {
            scanf("%s", maze[i]);
            for(int j=0; j<w; ++j)
            {
                if(maze[i][j] == 'S')
                {
                    sx = i;
                    sy = j;
                }
            }
        }
        //确定初始方位
        if(sx == 0)
            face = 2;
        else if(sx == h-1)
            face = 0;
        if(sy == 0)
            face = 1;
        else if(sy == w-1)
            face = 3;

        left = 1;
        leftDFS(sx, sy, face);
        right = 1;
        rightDFS(sx, sy, face);
        BFS(sx, sy);
    }
	return 0;
}

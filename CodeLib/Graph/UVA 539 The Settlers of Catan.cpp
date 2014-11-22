/*
** UVA 539 The Settlers of Catan
** Created by Rayn @@ 2014/04/17
** 回溯, 无向图的深度优先遍历
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 30;

int n, m, dis, ans;
int maze[MAX][MAX], vis[MAX];

void DFS(int pos, int len)
{
    if(len > dis)
        dis = len;
    for(int i=0; i<n; ++i)
    {
        if(maze[pos][i])
        {
            maze[pos][i] = maze[i][pos] = 0;
            vis[i] = 1;
            DFS(i, len+1);
            vis[i] = 0;
            maze[pos][i] = maze[i][pos] = 1;
        }
    }
}
int main()
{
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(!n && !m)
            break;
        int x, y;
        memset(maze, 0, sizeof(maze));
        memset(vis, 0, sizeof(vis));
        for(int i=0; i<m; ++i)
        {
            scanf("%d%d", &x, &y);
            maze[x][y] = 1;
            maze[y][x] = 1;
        }
        int ans = -1;
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(maze[i][j])
                {
                    dis = 0;
                    DFS(i, 0);
                    if(dis > ans)
                        ans = dis;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

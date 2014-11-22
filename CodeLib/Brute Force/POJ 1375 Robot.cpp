/*
** POJ 1375 Robot
** Created by Rayn @@ 2014/04/16
** BFSËÑË÷
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 64;

struct node{
    int x, y;
    int time, dir;
    node(int xx, int yy, int t, int d):
        x(xx),y(yy),time(t),dir(d) {}
};

int M, N, B1, B2, E1, E2, d;
int arr[MAX][MAX], vis[MAX][MAX][4];
int mov[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};/*n,e,s,w*/

queue <node> q;

void BFS(int x, int y, int dir)
{
    while(!q.empty())
        q.pop();

    vis[x][y][dir] = 1;
    q.push(node(x, y, 0, dir));
    while(!q.empty())
    {
        node now = q.front();
        if(now.x == E1 && now.y == E2)
        {
            printf("%d\n", now.time);
            return ;
        }
        q.pop();

        /* the GO command: step {1,2,3} */
        for(int i=1; i<=3; ++i)
        {
            node next = now;
            next.x += mov[now.dir][0] * i;
            next.y += mov[now.dir][1] * i;
            next.dir = now.dir;
            next.time += 1;
            if(next.x<=0 || next.y<=0 || next.x>=M || next.y>=N || arr[next.x][next.y])
                break;
            if(!arr[next.x][next.y] && !vis[next.x][next.y][next.dir])
            {
                vis[next.x][next.y][next.dir] = 1;
                q.push(next);
            }
        }
        node next = now;
        next.time += 1;
        /* The TURN command: turn right */
        next.dir = (now.dir + 3) % 4;
        if(!vis[next.x][next.y][next.dir])
        {
            vis[next.x][next.y][next.dir] = 1;
            q.push(next);
        }
        /* The TURN command: turn left */
        next.dir = (now.dir + 1) % 4;
        if(!vis[next.x][next.y][next.dir])
        {
            vis[next.x][next.y][next.dir] = 1;
            q.push(next);
        }
    }
    printf("-1\n");
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r",stdin);
#endif

    while(scanf("%d%d", &M, &N) != EOF)
    {
        if(!M && !N)
            break;

        memset(arr, 0, sizeof(arr));
        memset(vis, 0, sizeof(vis));
        int status;
        for(int i=0; i<M; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                scanf("%d", &status);
                if(status == 1)
                {
                    arr[i][j] = status;
                    arr[i+1][j] = status;
                    arr[i][j+1] = status;
                    arr[i+1][j+1] = status;
                }
            }
        }
        char Bdir[12];
        scanf("%d%d%d%d %s", &B1, &B2, &E1, &E2, Bdir);

        if(B1 == E1 && B2 == E2)
        {
            printf("0\n");
            continue;
        }
        if(Bdir[0] == 'n')
            d = 0;
        else if(Bdir[0] == 'e')
            d = 1;
        else if(Bdir[0] == 's')
            d = 2;
        else if(Bdir[0] == 'w')
            d = 3;

        BFS(B1, B2, d);
    }
    return 0;
}

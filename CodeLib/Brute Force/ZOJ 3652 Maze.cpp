/*
** ZOJ 3652 Maze
** Created by Rayn @@ 2014/07/30
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 60;
const int MAXM = (1<<6);
const int INF = 0x3F3F3F3F;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m, l, k;
int sx, sy, ex, ey;
int maze[MAXN][MAXN];
int monster[MAXN][MAXN];
int vis[MAXN][MAXN][MAXM];

struct State
{
    int x, y;
    int turn;   //回合
    int mobility;   //行动值
    int mask;   //怪物状态

    State() {}
    State(int x, int y, int turn, int mob, int mask):
        x(x), y(y), turn(turn), mobility(mob), mask(mask) {}

    bool operator < (const State& rhs) const {
        if(turn != rhs.turn)
            return turn > rhs.turn;
        return mobility < rhs.mobility;
    }
};

void Init()
{
    memset(maze, 0, sizeof(maze));
    memset(vis, 0, sizeof(vis));
    memset(monster, 0, sizeof(monster));
}
bool InRange(int x, int y)
{
    return (x >= 1 && y >= 1 && x <= n && y <= m);
}
void BFS()
{
    priority_queue<State> que;
    que.push(State(sx, sy, 1, l, 0));
    vis[sx][sy][0] = 1;

    while(!que.empty())
    {
        State now = que.top();
        if(now.x == ex && now.y == ey)
        {
            printf("%d\n", now.turn);
            return ;
        }
        que.pop();

        for(int i = 0; i < 4; ++i)
        {
            int px = now.x + dir[i][0];
            int py = now.y + dir[i][1];

            if(!InRange(px, py) || maze[px][py] == -1)
                continue;

            int nmob = now.mobility - 1;
            int nmask = now.mask;
            int nturn = now.turn + (nmob < 0? 1 : 0);

            if(nmob < 0)
                nmob = l - 1;

            if(maze[px][py] > 0)
            {
                if(!(nmask & (1 << (maze[px][py]-1))))
                {
                    nmob = 0;
                }
            }
            if(monster[px][py])
            {
                nmask = (nmask | (1 << (monster[px][py]-1)));
            }

            if(!vis[px][py][nmask])
            {
                vis[px][py][nmask] = 1;
                que.push(State(px, py, nturn, nmob, nmask));
            }
        }
    }
    printf("We need God's help!\n");
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d%d", &n, &m, &l) != EOF)
    {
        Init();
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                scanf("%d", &maze[i][j]);
            }
        }
        scanf("%d", &k);
        for(int i = 1, x, y; i <= k; ++i)
        {
            scanf("%d%d", &x, &y);
            monster[x][y] = i;
        }
        scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
        if(sx == ex && sy == ey)
        {
            printf("0\n");
            continue;
        }
        if(maze[sx][sy] == -1 || maze[ex][ey] == -1)
        {
            printf("We need God's help!\n");
            continue;
        }
        BFS();
    }
    return 0;
}

/*
** HDU 5025 Saving Tang Monk
** Created by Rayn @@ 2014/09/22
*/
#include <set>
#include <map>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <queue>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int INF = 0x3F3F3F3F;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct State
{
    int x, y, step, key, snake;
    State() {}
    State(int x, int y, int step, int key, int snake):
        x(x), y(y), step(step), key(key), snake(snake) {}
    bool operator < (const State & a) const
    {
        return step > a.step;
    }
};

int n, m, snake;
int sx, sy, ex, ey;
int maze[MAXN][MAXN];
bool vis[MAXN][MAXN][10][1<<5];

bool out(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= n)
        return true;
    return false;
}
int bfs()
{
    priority_queue<State> que;
    que.push(State(sx, sy, 0, 0, 0));
    vis[sx][sy][0][0] = 0;
    while(!que.empty())
    {
        State cur = que.top();
        que.pop();
        if(cur.x == ex && cur.y == ey && cur.key == m) {
            return cur.step;
        }
        for(int i = 0; i < 4; ++i) {
            int px = cur.x + dir[i][0];
            int py = cur.y + dir[i][1];
            if(out(px, py) || maze[px][py] == -1)
                continue;
            if(vis[px][py][cur.key][cur.snake]) {
                continue;
            }
            vis[px][py][cur.key][cur.snake] = true;
            if(maze[px][py] >= 10) {
                int s = maze[px][py] - 10;
                if(cur.snake & (1 << s)) {
                    que.push(State(px, py, cur.step + 1, cur.key, cur.snake));
                } else {
                    que.push(State(px, py, cur.step + 2, cur.key, cur.snake | (1 << s)));
                }
            } else if(maze[px][py] > 0) {
                if(maze[px][py] == cur.key + 1) {
                    que.push(State(px, py, cur.step + 1, cur.key + 1, cur.snake));
                } else {
                    que.push(State(px, py, cur.step + 1, cur.key, cur.snake));
                }
            } else if(maze[px][py] == 0) {
                que.push(State(px, py, cur.step + 1, cur.key, cur.snake));
            }
        }
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char line[MAXN];
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0) break;
        memset(maze, -1, sizeof(maze));
        memset(vis, false, sizeof(vis));
        snake = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%s", line);
            for(int j = 0; j < n; ++j) {
                if(line[j] == '.') {
                    maze[i][j] = 0;
                } else if(line[j] == 'K') {
                    sx = i;
                    sy = j;
                    maze[i][j] = 0;
                } else if(line[j] == 'T') {
                    ex = i;
                    ey = j;
                    maze[i][j] = 0;
                } else if(line[j] == 'S') {
                    maze[i][j] = 10 + snake;
                    snake++;
                } else if(isdigit(line[j])) {
                    int id = line[j] - '0';
                    maze[i][j] = id;
                }
            }
        }
        /*for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                printf("%d ", maze[i][j]);
            }
            puts("");
        }*/
        int res = bfs();
        if(res == -1) {
            printf("impossible\n");
        } else {
            printf("%d\n", res);
        }
    }
    return 0;
}

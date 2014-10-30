/*
** HDU 4771 Stealing Harry Potter's Precious
** Created by Rayn @@ 2014/09/10
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 108;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m, k;
int maze[MAXN][MAXN];
int step[MAXN][MAXN][1<<4];

struct State
{
    int x, y, s;
    State() {}
    State(int x, int y, int s):
        x(x), y(y), s(s) {}
};
bool out(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m)
        return true;
    return false;
}
int bfs(int sx, int sy, int status)
{
    memset(step, -1, sizeof(step));
    int ALL = (1 << k) - 1;

    queue<State> q;
    q.push(State(sx, sy, status));
    step[sx][sy][status] = 0;
    while(!q.empty())
    {
        State cur = q.front();
        q.pop();
        if(cur.s == ALL) {
            return step[cur.x][cur.y][cur.s];
        }
        for(int i = 0; i < 4; ++i) {
            int px = cur.x + dir[i][0];
            int py = cur.y + dir[i][1];
            if(out(px, py) || maze[px][py] == -1)
                continue;
            int s = cur.s | maze[px][py];
            if(step[px][py][s] == -1) {
                step[px][py][s] = step[cur.x][cur.y][cur.s] + 1;
                q.push(State(px, py, s));
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
    while(scanf("%d%d", &n, &m) != EOF && (n && m))
    {
        memset(maze, -1, sizeof(maze));
        int sx, sy, s = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%s", line);
            for(int j = 0; j < m; ++j) {
                if(line[j] == '@') {
                    sx = i, sy = j;
                    maze[i][j] = 0;
                } else if(line[j] == '.') {
                    maze[i][j] = 0;
                } else if(line[j] == '#'){
                    maze[i][j] = -1;
                }
            }
        }
        scanf("%d", &k);
        for(int i = 0, x, y; i < k; ++i) {
            scanf("%d%d", &x, &y);
            maze[--x][--y] = (1 << i);
            if(sx == x && sy == y) {
                s |= (1 << i);
            }
        }
        printf("%d\n", bfs(sx, sy, s));
    }
    return 0;
}

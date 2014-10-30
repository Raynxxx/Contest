/*
** HDU 5040 Instrusive
** Created by Rayn @@ 2014/09/23
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 510;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct State
{
    int x, y, t, k;
    State() {}
    State(int x, int y, int t, int k):
        x(x), y(y), t(t), k(k) {}
};

int n, sx, sy;
char s[MAXN][MAXN];
int maze[MAXN][MAXN];
bool vis[MAXN][MAXN][3];

void Input()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", s[i]);
        for(int j = 0; j < n; ++j) {
            switch(s[i][j]) {
                case 'N': maze[i][j] = 0; break;
                case 'E': maze[i][j] = 1; break;
                case 'S': maze[i][j] = 2; break;
                case 'W': maze[i][j] = 3; break;
                default: maze[i][j] = -1; break;
            }
            if(s[i][j] == 'M') {
                sx = i; sy = j;
            }
        }
    }
}
inline bool InRange(int x, int y)
{
    return (x >= 0 && x < n && y >= 0 && y < n);
}
bool Capture(int x, int y, int t)
{
    if(maze[x][y] >= 0) return true;
    for(int i = 0; i < 4; ++i) {
        int px = x - dx[i];
        int py = y - dy[i];
        if(InRange(px, py) && maze[px][py] >= 0) {
            if((maze[px][py] + t) % 4 == i)
                return true;
        }
    }
    return false;
}
void Push(queue<State>& que, int x, int y, int t, int k)
{
    if(!vis[x][y][k]) {
        que.push(State(x, y, t, k));
        vis[x][y][k] = true;
    }
}
int bfs(int x, int y)
{
    memset(vis, false, sizeof(vis));
    queue<State> que;
    Push(que, x, y, 0, 0);
    while(!que.empty())
    {
        int x = que.front().x;
        int y = que.front().y;
        int t = que.front().t;
        int k = que.front().k;
        //printf("%d %d %d %d\n", x, y, t, k);
        que.pop();
        if(k) {
            if(k == 1 && s[x][y] == 'T') return t + 1;
            Push(que, x, y, t + 1, k - 1);
            continue;
        }
        bool f = Capture(x, y, t);
        for(int i = 0; i < 4; ++i) {
            int px = x + dx[i];
            int py = y + dy[i];
            if(!InRange(px, py) || s[px][py] == '#') continue;
            if(f || Capture(px, py, t)) {
                for(int j = 1; j <= 2; ++j) {
                    if(j == 2 || (!Capture(x, y, t + j) && !Capture(px, py, t + j))) {
                        Push(que, px, py, t + 1, j);
                        break;
                    }
                }
            } else {
                if(s[px][py] == 'T') return t + 1;
                Push(que, px, py, t + 1, 0);
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
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        Input();
        printf("Case #%d: %d\n", ++cases, bfs(sx, sy));
    }
    return 0;
}

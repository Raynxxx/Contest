/*
** HDU 1253 胜利大逃亡
** Created by Rayn @@ 2014/07/19
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 55;

struct Node
{
    int x, y, z;
    int time;
    Node() {}
    Node(int x, int y, int z, int t): x(x), y(y), z(z), time(t) {}
};

int A, B, C, T;
int maps[MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN];
int dir[][3] = {{1, 0, 0}, {-1, 0, 0},
                {0, 1, 0}, {0, -1, 0},
                {0, 0, 1}, {0, 0, -1}};
Node End;

bool OutSide(int x, int y, int z)
{
    if(x < 0 || y < 0 || z < 0 || x >= A || y >= B || z >= C)
        return true;
    return false;
}
int BFS(int sx, int sy, int sz)
{
    queue<Node> que;
    memset(vis, false, sizeof(vis));
    que.push(Node(sx, sy, sz, 0));
    vis[sx][sy][sz] = true;
    while(!que.empty())
    {
        Node now = que.front();
        que.pop();
        if(now.time > T)
        {
            return -1;
        }
        if(now.x == End.x && now.y == End.y && now.z == End.z && now.time <= T)
        {
            return now.time;
        }
        for(int i = 0; i < 6; ++i)
        {
            Node tmp = now;
            tmp.x += dir[i][0];
            tmp.y += dir[i][1];
            tmp.z += dir[i][2];
            tmp.time += 1;
            if(OutSide(tmp.x, tmp.y, tmp.z) || maps[tmp.x][tmp.y][tmp.z] ||
                vis[tmp.x][tmp.y][tmp.z])
                continue;
            vis[tmp.x][tmp.y][tmp.z] = true;
            que.push(tmp);
        }
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%d%d", &A, &B, &C, &T);
        for(int i = 0; i < A; ++i)
        {
            for(int j = 0; j < B; ++j)
            {
                for(int k = 0; k < C; ++k)
                {
                    scanf("%d", &maps[i][j][k]);
                }
            }
        }
        End = Node(A-1, B-1, C-1, T);
        printf("%d\n", BFS(0, 0, 0));
    }
    return 0;
}

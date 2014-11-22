/*
** HDU 1507 Uncle Tom's Inherited Land
** Created by Rayn @@ 2014/07/18
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct List
{
    int x, y;
    List(int x=0, int y=0):
        x(x), y(y) {}
} path[MAXN*MAXN];

int n, m;
int mark[MAXN][MAXN], color[MAXN];
bool vis[MAXN];
int link1[MAXN], link2[MAXN];
int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Hungarian
{
    int n;
    int edge[MAXN][MAXN];
    bool used[MAXN];

    void Init(int n)
    {
        this->n = n;
        memset(edge, 0, sizeof(edge));
    }
    bool Find(int u)
    {
        for(int i = 1; i <= n; ++i)
        {
            if(edge[u][i] && !used[i] && !color[i])
            {
                used[i] = true;
                if(!link2[i] || Find(link2[i]))
                {
                    link1[u] = i;
                    link2[i] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch()
    {
        int res = 0;
        memset(link1, 0, sizeof(link1));
        memset(link2, 0, sizeof(link2));
        for(int i = 1; i <= n; ++i)
        {
            memset(used, false, sizeof(used));
            if(!link1[i] && color[i])
            {
                if(Find(i))
                {
                    res++;
                }
            }
        }
        return res;
    }
};

void Color(int x, int y, int c) //½»²æÈ¾É«
{
    for(int i = 0; i < 4; ++i)
    {
        int px = x + dir[i][0];
        int py = y + dir[i][1];
        if(px <= 0 || px > n || py <= 0 || py > m)
            continue;
        if(mark[px][py] > 0 && color[mark[px][py]] == -1)
        {
            color[mark[px][py]] = !c;
            Color(px, py, !c);
        }
    }
}
Hungarian Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int k, x, y;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0)
            break;

        scanf("%d", &k);
        memset(mark, 0, sizeof(mark));
        memset(path, 0, sizeof(path));
        memset(color, -1, sizeof(color));

        for(int i = 0; i < k; ++i)
        {
            scanf("%d%d", &x, &y);
            mark[x][y] = -1;
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                if(mark[i][j] == 0)
                {
                    cnt++;
                    mark[i][j] = cnt;
                    path[cnt] = List(i, j);
                }
            }
        }
        Solver.Init(cnt);
        //ºÚ°×È¾É«
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= m; ++j)
            {
                if(mark[i][j] > 0 && color[mark[i][j]] == -1)
                {
                    color[mark[i][j]] = 0;
                    Color(i, j, 0);
                }
            }
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    int px = i + dir[k][0];
                    int py = j + dir[k][1];
                    if(px <= 0 || px > n || py <= 0 || py > m)
                        continue;
                    if(color[mark[i][j]] && !color[mark[px][py]])
                    {
                        Solver.edge[mark[i][j]][mark[px][py]] = 1; //µ¥ÏòÍ¼,ºÚ->°×±ß
                    }
                }
            }
        }
        int sum = Solver.MaxMatch();
        printf("%d\n", sum);
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= cnt; ++i)
        {
            if(link1[i] && !vis[i] && !vis[link1[i]])
            {
                vis[i] = vis[link1[i]] = true;
                //printf("link1[%d] = %d\n", i, link1[i]);
                printf("(%d,%d)--(%d,%d)\n", path[i].x, path[i].y, path[link1[i]].x, path[link1[i]].y);
            }
        }
        printf("\n");
    }
    return 0;
}

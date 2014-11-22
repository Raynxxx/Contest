/*
** HDU 2389 Rain on your Parade
** Created by Rayn @@ 2014/07/23
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 3010;
const double EPS = 1e-10;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};
//Hopcroft-Karp算法，解决二分图最大匹配
//比匈牙利稍快
struct HopcroftKarp
{
    int n;
    int dy[MAXN], dx[MAXN];
    int xlink[MAXN], ylink[MAXN];
    int edge[MAXN][MAXN];

    void InitGraph(int n)
    {
        this->n = n;
        memset(edge, 0, sizeof(edge));
    }
    void AddEdge(int from, int to)
    {
        edge[from][++edge[from][0]] = to;
    }
    void GreedyInit(int& cnt)
    {
        memset(xlink, -1, sizeof(xlink));
        memset(ylink, -1, sizeof(ylink));
        for(int u = 1; u <= n; ++u)
        {
            for(int i = 1; i <= edge[u][0]; ++i)
            {
                int v = edge[u][i];
                if(ylink[v] == -1)
                {
                    ylink[v] = u;
                    xlink[u] = v;
                    cnt++;
                    break;
                }
            }
        }
    }
    bool DFS(int u)
    {
        for(int i = 1; i <= edge[u][0]; ++i)
        {
            int v = edge[u][i];
            if(dy[v] == dx[u] + 1)
            {
                dy[v] = 0;
                if(ylink[v] == -1 || DFS(ylink[v]))
                {
                    ylink[v] = u;
                    xlink[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    bool BFS()
    {
        queue<int> que;
        memset(dx, 0, sizeof(dx));
        memset(dy, 0, sizeof(dy));
        for(int i = 1; i <= n; ++i)
        {
            if(xlink[i] == -1)
                que.push(i);
        }
        bool flag = false;
        while(!que.empty())
        {
            int u = que.front();
            que.pop();
            for(int i = 1; i <= edge[u][0]; ++i)
            {
                int v = edge[u][i];
                if(dy[v] == 0)
                {
                    dy[v] = dx[u] + 1;
                    if(ylink[v] == -1)
                    {
                        flag = true;
                    }
                    else
                    {
                        dx[ylink[v]] = dy[v] + 1;
                        que.push(ylink[v]);
                    }
                }
            }
        }
        return flag;
    }
    int MaxMatch()
    {
        int cnt = 0;
        GreedyInit(cnt);
        while(BFS())
        {
            for(int i = 1; i <= n; ++i)
            {
                if(xlink[i] == -1 && DFS(i))
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

struct Guest
{
    int x, y;
    int speed;
};
typedef Guest Umbrella;

double Distance(const Guest& A, const Umbrella& B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

HopcroftKarp Solver;
Guest peo[MAXN];
Umbrella umb[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, cases = 0;
    int time, m, n;
    int x, y, speed;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &time, &m);
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d%d%d", &peo[i].x, &peo[i].y, &peo[i].speed);
        }
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d%d", &umb[i].x, &umb[i].y);
        }
        Solver.InitGraph(m);
        for(int i = 1; i <= m; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                double dis = Distance(peo[i], umb[j]);
                if(dis/peo[i].speed < time + EPS)
                {
                    Solver.AddEdge(i, j);
                }
            }
        }
        printf("Scenario #%d:\n", ++cases);
        printf("%d\n\n", Solver.MaxMatch());
    }
    return 0;
}

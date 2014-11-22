/*
** POJ 3041 Asteroids
** Created by Rayn @@ 2014/07/23
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 510;
const int MAXM = 10010;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};
struct HopcroftKarp
{
    int n;
    int dy[MAXN], dx[MAXN];
    int xlink[MAXN], ylink[MAXN];
    vector<Edge> edge;
    vector<int> G[MAXN];

    void InitGraph(int n)
    {
        this->n = n;
        for(int i = 0; i <= n; ++i)
            G[i].clear();
        edge.clear();
        edge.reserve(MAXM);
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        G[from].push_back((int)edge.size() - 1);
    }
    void GreedyInit(int& cnt)
    {
        memset(xlink, -1, sizeof(xlink));
        memset(ylink, -1, sizeof(ylink));
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 0; j < (int) G[i].size(); ++j)
            {
                int v = edge[G[i][j]].to;
                if(ylink[v] == -1)
                {
                    ylink[v] = i;
                    xlink[i] = v;
                    cnt++;
                    break;
                }
            }
        }
    }
    bool DFS(int u)
    {
        for(int i = 0; i < (int) G[u].size(); ++i)
        {
            int v = edge[G[u][i]].to;
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
        for(int i = 1; i <= n; ++i)
        {
            if(xlink[i] == -1) {
                que.push(i);
            }
        }
        memset(dx, 0, sizeof(dx));
        memset(dy, 0, sizeof(dy));
        bool flag = false;
        while(!que.empty())
        {
            int u = que.front();
            que.pop();
            for(int i = 0; i < (int) G[u].size(); ++i)
            {
                int v = edge[G[u][i]].to;
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
                    cnt++;
            }
        }
        return cnt;
    }
};

HopcroftKarp Solver;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, k, r, c;

    while(scanf("%d%d", &n, &k) != EOF)
    {
        Solver.InitGraph(n);
        for(int i = 0; i < k; ++i)
        {
            scanf("%d%d", &r, &c);
            Solver.AddEdge(r, c, 1);
        }
        printf("%d\n", Solver.MaxMatch());
    }
    return 0;
}

/*
** HDU 2444 The Accomodation of Students
** Created by Rayn @@ 2014/07/22
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 210;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int n;
    bool flag;
    bool used[MAXN];
    int link[MAXN];
    int color[MAXN];
    vector<Edge> edge;
    vector<int> G[MAXN];

    void Init(int n)
    {
        this->n = n;
        memset(color, 0, sizeof(color));
        for(int i = 0; i <= n; ++i)
            G[i].clear();
        edge.clear();
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        int m = edge.size();
        G[from].push_back(m-1);
    }
    void CheckDFS(int u, int col)
    {
        for(int i = 0; i < (int) G[u].size(); ++i)
        {
            int v = edge[G[u][i]].to;
            if(!color[v])
            {
                color[v] = -color[u];
                CheckDFS(v, color[v]);
            }
            else if(color[v] == col)
            {
                flag = false;
                return ;
            }
            if(!flag)
            {
                return ;
            }
        }
    }
    bool Check()
    {
        flag = true;
        color[1] = 1;
        CheckDFS(1, color[1]);
        return flag;
    }
    int MaxMatch()
    {
        int sum = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= n; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i))
                sum++;
        }
        return sum;
    }
    bool Find(int u)
    {
        for(int i = 0; i < (int) G[u].size(); ++i)
        {
            int v = edge[G[u][i]].to;
            if(!used[v])
            {
                used[v] = true;
                if(link[v] == -1 || Find(link[v]))
                {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
};

Hungarian Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, m, x, y;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Solver.Init(n);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d", &x, &y);
            Solver.AddEdge(x, y, 1);
            Solver.AddEdge(y, x, 1);
        }
        if(!Solver.Check())
        {
            printf("No\n");
            continue;
        }
        printf("%d\n", Solver.MaxMatch()/2);
    }
    return 0;
}

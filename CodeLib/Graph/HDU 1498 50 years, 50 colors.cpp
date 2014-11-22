/*
** HDU 1498 50 years, 50 colors
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int left, right;
    vector<Edge> edge;
    vector<int> G[MAXN];
    int link[MAXN];
    bool used[MAXN];

    void Init(int n, int m)
    {
        this->left = n;
        this->right = m;
        for(int i = 0; i <= n; ++i)
        {
            G[i].clear();
            G[i].reserve(MAXN);
        }
        edge.clear();
        edge.reserve(MAXN);
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        int m = edge.size();
        G[from].push_back(m-1);
    }
    bool Find(int u, int val)
    {
        int s = G[u].size();
        for(int i = 0; i < s; ++i)
        {
            int v = edge[G[u][i]].to;
            int w = edge[G[u][i]].weight;
            if(!used[v] && w == val)
            {
                used[v] = true;
                if(link[v] == -1 || Find(link[v], val))
                {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch(int val)
    {
        int cnt = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= left; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i, val)) {
                cnt++;
            }
        }
        return cnt;
    }
};

Hungarian Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, k, color[MAXN];
    bool have[51];
    while(scanf("%d%d", &n, &k) != EOF && (n && k))
    {
        memset(have, false, sizeof(have));
        Solver.Init(n, n);
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                int val;
                scanf("%d", &val);
                Solver.AddEdge(i, j, val);
                if(!have[val])
                {
                    have[val] = true;
                    color[cnt++] = val;
                }
            }
        }
        sort(color, color+cnt);
        bool flag = true, first = true;
        for(int i = 0; i < cnt; ++i)
        {
            if(Solver.MaxMatch(color[i]) > k)
            {
                flag = false;
                if(!first)
                    printf(" ");
                printf("%d", color[i]);
                first = false;
            }
        }
        if(flag)
            printf("-1\n");
        else
            printf("\n");
    }
    return 0;
}

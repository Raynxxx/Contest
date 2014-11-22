/*
** POJ 1860 Currency Exchange
** Created by Rayn @@ 2014/07/10
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 110;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to;
    double rate, com;
    Edge() {}
    Edge(int from, int to, double rate, double com):
        from(from), to(to), rate(rate), com(com) {}
};
//×î¶ÌÂ·(SPFA)
struct SPFA
{
    int n, m;
    vector<Edge> edge;
    vector<int> G[MAXN];
    bool inq[MAXN];
    int cnt[MAXN];
    double dis[MAXN];

    SPFA(int n = 0)
    {
        this->n = n;
        for(int i = 0; i <= n; ++i)
        {
            G[i].clear();
            G[i].reserve(MAXN);
        }
        edge.clear();
        edge.reserve(MAXN*MAXN);
    }
    void AddEdge(int from, int to, double rat, double com)
    {
        edge.push_back(Edge(from, to, rat, com));
        m = edge.size();
        G[from].push_back(m-1);
    }
    bool BellmanFord(int S, double V)
    {
        queue<int> que;
        memset(inq, false, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        memset(dis, 0, sizeof(dis));

        que.push(S);
        dis[S] = V;
        inq[S] = true;
        cnt[S]++;
        while(!que.empty())
        {
            if(dis[S] > V)
                return true;
            int u = que.front();
            que.pop();
            inq[u] = false;
            for(int i = 0; i < (int) G[u].size(); ++i)
            {
                Edge& e = edge[G[u][i]];
                if(dis[e.to] < (dis[u]-e.com) * e.rate)
                {
                    dis[e.to] = (dis[u]-e.com) * e.rate;
                    if(!inq[e.to])
                    {
                        que.push(e.to);
                        inq[e.to] = true;
                        if(++cnt[e.to] > n)
                            return true;
                    }
                }
            }
        }
        return false;
    }
    int GetDis(int dest)
    {
        return dis[dest];
    }
};

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int N, M, S;
    double V, rate, com;
    int a, b;

    while(scanf("%d%d%d%lf", &N, &M, &S, &V) != EOF)
    {
        SPFA solver(N);
        for(int i = 0; i < M; ++i)
        {
            scanf("%d%d%lf%lf", &a, &b, &rate, &com);
            solver.AddEdge(a, b, rate, com);
            scanf("%lf%lf", &rate, &com);
            solver.AddEdge(b, a, rate, com);
        }
        if(solver.BellmanFord(S, V))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

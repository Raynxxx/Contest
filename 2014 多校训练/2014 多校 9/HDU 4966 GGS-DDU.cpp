/*
** HDU 4966 GGS-DDU
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 1024;
const int MAXM = MAXN * MAXN;

struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w):
        u(u), v(v), w(w) {}
};

struct DirectedMST
{
    int n, m;
    int id[MAXN];
    int in[MAXN];
    int pre[MAXN];
    int vis[MAXN];
    Edge edge[MAXM];

    void Init(int n)
    {
        this->n = n;
        this->m = 0;
    }
    void AddEdge(int u, int v, int w)
    {
        edge[m++] = Edge(u, v, w);
    }
    int Gao(int root)
    {
        int ret = 0;
        while(true)
        {
            fill(id, id + n, -1);
            fill(vis, vis + n, -1);
            fill(in, in + n, INF);
            for(int i = 0; i < m; ++i)
            {
                Edge& e = edge[i];
                if(in[e.v] > e.w && e.u != e.v) {
                    pre[e.v] = e.u;
                    in[e.v] = e.w;
                }
            }
            in[root] = 0;
            pre[root] = root;
            for(int i = 0; i < n; ++i)
            {
                ret += in[i];
                if(in[i] == INF) {
                    return -1;
                }
            }
            int cnt = 0;
            for(int i = 0; i < n; ++i)
            {
                if(vis[i] == -1)
                {
                    int u = i;
                    while(vis[u] == -1)
                    {
                        vis[u] = i;
                        u = pre[u];
                    }
                    if(vis[u] != i || u == root) continue;
                    for(int j = pre[u]; j != u; j = pre[j])
                    {
                        id[j] = cnt;
                    }
                    id[u] = cnt++;
                }
            }
            if(cnt == 0) break;
            for(int i = 0; i < n; ++i)
            {
                if(id[i] == -1) {
                    id[i] = cnt++;
                }
            }
            for(int i = 0; i < m; ++i)
            {
                int u = edge[i].u;
                int v = edge[i].v;
                edge[i].u = id[u];
                edge[i].v = id[v];
                edge[i].w -= in[v];
            }
            this->n = cnt;
            root = id[root];
        }
        return ret;
    }
};

DirectedMST Solver;
int N, M, S, T;
int a[MAXN], presum[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &N, &M) != EOF && (N && M))
    {
        presum[0] = 0;
        for(int i = 1; i <= N; ++i)
        {
            scanf("%d", &a[i]);
            presum[i] = presum[i-1] + a[i] + 1;
        }
        int Source = 0;
        Solver.Init(presum[N] + 1);
        for(int i = 1; i <= N; ++i)
        {
            Solver.AddEdge(Source, presum[i-1]+1, 0);
            for(int j = 1; j < a[i] + 1; ++j)
            {
                int degree = presum[i-1] + j;
                Solver.AddEdge(degree+1, degree, 0);
            }
        }
        for(int i = 1; i <= M; ++i)
        {
            int c, L1, d, L2, money;
            scanf("%d%d%d%d%d", &c, &L1, &d, &L2, &money);
            L1++, L2++;
            Solver.AddEdge(presum[c-1] + L1, presum[d-1] + L2, money);
        }
        int res = Solver.Gao(Source);
        if(res >= 0) {
            printf("%d\n", res);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}

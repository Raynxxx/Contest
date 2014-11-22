/*
** ZOJ 3795 Grouping
** Created by Rayn @@ 2014/08/14
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;
const int MAXM = 300010;

struct Edge
{
    int from, to, next;
    Edge() {}
    Edge(int from, int to, int next):
        from(from), to(to), next(next) {}
};

int n, m;
int sz, ssz;
int dfn, top, ssn;
int sstack[MAXN], sid[MAXN];
int head[MAXN], shead[MAXN];
int low[MAXN], dep[MAXN];
int check[MAXN], mark[MAXN], cnt[MAXN];
Edge edge[MAXM], sedge[MAXM];

void Init()
{
    sz = ssz = 0;
    memset(head, -1, sizeof(head));
    memset(shead, -1, sizeof(shead));
}
void AddEdge(Edge e[], int pre[], int& m, int from, int to)
{
    e[m] = Edge(from, to, pre[from]);
    pre[from] = m++;
}
void Tarjan(int u)
{
    mark[u] = low[u] = dfn++;
    check[u] = 1;
    sstack[top++] = u;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!mark[v]) {
            Tarjan(v);
            low[u] = min(low[v], low[u]);
        } else if (check[v]) {
            low[u] = min(low[u], mark[v]);
        }
    }
    if (mark[u] == low[u]) {
        while (sstack[--top] != u) {
            check[sstack[top]] = 0;
            sid[sstack[top]] = ssn;
            cnt[ssn]++;
        }
        sid[u] = ssn;
        cnt[ssn]++;
        check[u] = 0;
        ++ssn;
    }
}
void FindSCC()
{
    memset(check, 0, sizeof(check));
    memset(mark, 0, sizeof(mark));
    memset(cnt, 0, sizeof(cnt));
    ssn = dfn = 1;
    top = 0;
    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            Tarjan(i);
        }
    }
}
void dfs(int u)
{
    check[u] = 1;
    dep[u] = cnt[u];
    for (int i = shead[u]; i != -1; i = sedge[i].next)
    {
        int v = sedge[i].to;
        if (!check[v]) {
            dfs(v);
        }
        if (dep[v] + cnt[u] > dep[u]) {
            dep[u] = dep[v] + cnt[u];
        }
    }
}
int Solve()
{
    memset(check, 0, sizeof(check));
    memset(dep, 0, sizeof(dep));
    for (int i = 1; i < ssn; ++i) {
        if(!check[i]) {
            dfs(i);
        }
    }
    int res = 0;
    for (int i = 1; i < ssn; ++i) {
        if (dep[i] > res) {
            res = dep[i];
        }
    }
    return res;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &n, &m) != EOF)
    {
        Init();
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            AddEdge(edge, head, sz, x, y);
        }
        FindSCC();
        for (int i = 0; i < sz; ++i)
        {
            int u = edge[i].from;
            int v = edge[i].to;
            if (sid[u] != sid[v])
            {
                AddEdge(sedge, shead, ssz, sid[u], sid[v]);
            }
        }
        printf("%d\n", Solve());
    }
    return 0;
}

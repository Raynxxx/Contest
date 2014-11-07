/*
** HDU 4738 Caocao's Bridges
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 1005;
const int MAXM = MAXN*MAXN*2;
const int INF = 1 << 28;

//UnionSet part
int pa[MAXN], rnk[MAXN];
void MakeSet(int n)
{
    for(int i = 0; i <= n; ++i) {
        pa[i] = i;
        rnk[i] = 1;
    }
}
int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
void UnionSet(int x, int y)
{
    int px = FindSet(x);
    int py = FindSet(y);
    if(px == py) return ;
    if(rnk[px] > rnk[py]) {
        pa[py] = px;
        rnk[px] += rnk[py];
    } else {
        pa[px] = py;
        rnk[py] += rnk[px];
    }
}

struct Edge
{
    int to, w, next;
    bool cut;
    Edge() {}
    Edge(int to, int w, bool cut, int next):
        to(to), w(w), cut(cut), next(next) {}
};

//Tarjan part
Edge edge[MAXM];
int sz, cnt;
int head[MAXN];
int low[MAXN];
int dfn[MAXN];
int res;

void AddEdge(int u, int v, int w)
{
    edge[sz] = Edge(v, w, false, head[u]);
    head[u] = sz++;
    edge[sz] = Edge(u, w, false, head[v]);
    head[v] = sz++;
}
void Tarjan(int u, int pre)
{
    low[u] = dfn[u] = ++cnt;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        if(i == (pre^1)) continue;
        int v = edge[i].to;
        if(!dfn[v]) {
            Tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {
                res = min(res, edge[i].w);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

//solve problem part
void Init(int n)
{
    sz = cnt = 0;
    MakeSet(n);
    memset(head, -1, sizeof(int)*(n+1));
    memset(dfn, 0, sizeof(dfn));
}
bool IsLinkGraph(int n)
{
    for(int i = 2; i <= n; ++i) {
        if(FindSet(i) != FindSet(i-1)) {
            return false;
        }
    }
    return true;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF && (n && m))
    {
        Init(n);
        for(int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w);
            UnionSet(u, v);
        }
        if(!IsLinkGraph(n)) {
            printf("0\n");
            continue;
        }
        res = INF;
        Tarjan(1, -1);
        if(res == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", max(res, 1));
        }
    }
    return 0;
}

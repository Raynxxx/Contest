/*
** CF 258E Little Elephant and Tree
** Created by Rayn @@ 2014/09/27
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

#define lson (rt<<1)
#define rson (rt<<1|1)
const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

class DFS_SegmentTree {
public:
    struct Edge {
        int to, next;
        Edge() {}
        Edge(int to, int next): to(to), next(next) {}
    };

    Edge edge[MAXN<<1];
    int tot, head[MAXN];
    int dfn, in[MAXN], out[MAXN];

    void Init()
    {
        dfn = tot = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int u, int v)
    {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void dfs(int u, int pre)
    {
        in[u] = ++dfn;
        //printf(" %d ", in[u]);
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(v == pre) continue;
            dfs(v, u);
        }
        out[u] = dfn;
        //printf(" %d ", out[u]);
    }

    struct Node {
        int l, r;
        int sum, tag;
        inline int Mid() {
            return (l + r) >> 1;
        }
        inline int Range() {
            return r - l + 1;
        }
    };

    Node tree[MAXN<<2];

    void Build(int rt, int l, int r)
    {
        tree[rt].l = l, tree[rt].r = r;
        tree[rt].sum = tree[rt].tag = 0;
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
    inline void PushUp(int rt)
    {
        if(tree[rt].tag) {
            tree[rt].sum = tree[rt].Range();
        } else {
            if(tree[rt].l == tree[rt].r) {
                tree[rt].sum = 0;
            } else {
                tree[rt].sum = tree[lson].sum + tree[rson].sum;
            }
        }
    }
    void Update(int rt, int x, int y, int c)
    {
        if(x <= tree[rt].l && tree[rt].r <= y) {
            tree[rt].tag += c;
            PushUp(rt);
            return ;
        }
        int mid = tree[rt].Mid();
        if(x <= mid)
            Update(lson, x, y, c);
        if(mid < y)
            Update(rson, x, y, c);
        PushUp(rt);
    }
    void Update(int top, int c) {
        Update(1, in[top], out[top], c);
    }
};

int ret[MAXN];
vector<int> query[MAXN];
DFS_SegmentTree st;

void Pre(int n, int m)
{
    st.Init();
    for(int i = 1; i <= n; ++i) {
        query[i].clear();
    }
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        st.AddEdge(u, v);
        st.AddEdge(v, u);
    }
    for(int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        query[a].push_back(a);
        query[a].push_back(b);
        query[b].push_back(b);
        query[b].push_back(a);
    }
    st.dfs(1, -1);
    st.Build(1, 1, n);
}
void Gao(int u, int pre)
{
    for(int i = 0; i < (int) query[u].size(); ++i) {
        int top = query[u][i];
        st.Update(top, 1);
    }
    ret[u] = st.tree[1].sum;
    if(ret[u] > 0) ret[u]--;
    for(int i = st.head[u]; i != -1; i = st.edge[i].next) {
        int v = st.edge[i].to;
        if(v == pre) continue;
        Gao(v, u);
    }
    for(int i = 0; i < (int) query[u].size(); ++i) {
        int top = query[u][i];
        st.Update(top, -1);
    }
}
void nextGao(int n)
{
    for(int i = 1; i <= n; ++i) {
        printf("%d%c", ret[i], (i == n)? '\n' : ' ');
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        Pre(n, m);
        Gao(1, -1);
        nextGao(n);
    }
    return 0;
}

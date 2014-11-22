/*
** SPOJ Query on a tree
** Created by Rayn @@ 2014/09/24
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
    return ret;
}
const int MAXN = 10010;
const int INF = 0x3F3F3F3F;

class SegmentTree {
public:
    struct Node {
        int l, r;
        int maxv;
        inline int Mid() {
            return (l + r) >> 1;
        }
    };

    Node tree[MAXN<<2];

    void PushUp(int rt) {
        tree[rt].maxv = max(tree[lson].maxv, tree[rson].maxv);
    }
    void Build(int rt, int l, int r) {
        tree[rt].l = l, tree[rt].r = r;
        if(l == r) {
            tree[rt].maxv = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        PushUp(rt);
    }
    void Modify(int rt, int pos, int v) {
        if(tree[rt].l == pos && tree[rt].r == pos) {
            tree[rt].maxv = v;
            return ;
        }
        int mid = tree[rt].Mid();
        if(pos <= mid)
            Modify(lson, pos, v);
        else
            Modify(rson, pos, v);
        PushUp(rt);
    }
    int Query(int rt, int x, int y) {
        if(x <= tree[rt].l && tree[rt].r <= y) {
            return tree[rt].maxv;
        }
        int mid = tree[rt].Mid();
        int ret = -INF;
        if(x <= mid)
            ret = max(ret, Query(lson, x, y));
        if(mid < y)
            ret = max(ret, Query(rson, x, y));
        return ret;
    }
};

class HeavylightDecompose {
public:
    struct Edge {
        int to, next;
        Edge() {}
        Edge(int to, int next): to(to), next(next) {}
    };

    Edge edge[MAXN<<1];
    int tot, head[MAXN];
    int pos, top[MAXN], fa[MAXN], deep[MAXN];
    int num[MAXN], son[MAXN], p[MAXN], fp[MAXN];
    int node[MAXN][3];
    SegmentTree st;

    void Init() {
        tot = 0;
        pos = 1;
        memset(head, -1, sizeof(head));
        memset(son, -1, sizeof(son));
    }
    void Build(int n) {
        dfs1(1, 1, 1);
        dfs2(1, 1);
        st.Build(1, 1, pos-1);
        for(int i = 1; i < n; ++i) {
            if(deep[node[i][0]] > deep[node[i][1]]) {
                swap(node[i][0], node[i][1]);
            }
            st.Modify(1, p[node[i][1]], node[i][2]);
        }
    }
    void AddEdge(int u, int v) {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void dfs1(int u, int pre, int d) {
        deep[u] = d;
        fa[u] = pre;
        num[u] = 1;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(v != pre) {
                dfs1(v, u, d + 1);
                num[u] += num[v];
                if(son[u] == -1 || num[v] > num[son[u]]) {
                    son[u] = v;
                }
            }
        }
    }
    void dfs2(int u, int tp) {
        top[u] = tp;
        p[u] = pos++;
        fp[p[u]] = u;
        if(son[u] == -1) return ;
        dfs2(son[u], tp);
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(v != son[u] && v != fa[u]) {
                dfs2(v, v);
            }
        }
    }
    int GetMax(int u, int v) {
        int f1 = top[u], f2 = top[v];
        int ret = -INF;
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            ret = max(ret, st.Query(1, p[f1], p[u]));
            u = fa[f1];
            f1 = top[u];
        }
        if(u == v) return ret;
        if(deep[u] > deep[v]) swap(u, v);
        ret = max(ret, st.Query(1, p[son[u]], p[v]));
        return ret;
    }
    void Update(int u, int v) {
        st.Modify(1, p[node[u][1]], v);
    }
};

HeavylightDecompose hld;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        hld.Init();
        scanf("%d", &n);
        for(int i = 1; i < n; ++i) {
            hld.node[i][0] = nextInt();
            hld.node[i][1] = nextInt();
            hld.node[i][2] = nextInt();
            hld.AddEdge(hld.node[i][0], hld.node[i][1]);
            hld.AddEdge(hld.node[i][1], hld.node[i][0]);
        }
        hld.Build(n);
        char op[10];
        while(scanf("%s", op) && op[0] != 'D') {
            int a = nextInt();
            int b = nextInt();
            if(op[0] == 'C') {
                hld.Update(a, b);
            } else if(op[0] == 'Q') {
                printf("%d\n", hld.GetMax(a, b));
            }
        }
    }
    return 0;
}

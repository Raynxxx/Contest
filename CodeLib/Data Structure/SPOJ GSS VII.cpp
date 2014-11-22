/*
** SPOJ Can you answer these queries VII
** Created by Rayn @@ 2014/09/25
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

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
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


#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;
const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

class SegmentTree {
public:
    struct Node {
        int l, r;
        int tag;
        int sum, lmax, rmax, smax;
        inline int Mid() {
            return (l + r) >> 1;
        }
        inline int Range() {
            return (r - l + 1);
        }
        inline void take(const int& v) {
            lmax = rmax = smax = v;
        }
    };

    Node tree[MAXN<<2];

    inline Node Merge(const Node& L, const Node& R) {
        if(L.sum == -INF) return R;
        if(R.sum == -INF) return L;
        Node ret;
        ret.sum = L.sum + R.sum;
        ret.lmax = max(L.lmax, L.sum + R.lmax);
        ret.rmax = max(R.rmax, R.sum + L.rmax);
        ret.smax = max(max(L.smax, R.smax), L.rmax + R.lmax);
        ret.smax = max(ret.smax, max(ret.lmax, ret.rmax));
        return ret;
    }
    inline Node PushUp(Node& ret, const Node& L, const Node& R) {
        ret.sum = L.sum + R.sum;
        ret.lmax = max(L.lmax, L.sum + R.lmax);
        ret.rmax = max(R.rmax, R.sum + L.rmax);
        ret.smax = max(max(L.smax, R.smax), L.rmax + R.lmax);
        ret.smax = max(ret.smax, max(ret.lmax, ret.rmax));
    }
    inline void PushDown(int rt) {
        if(tree[rt].tag != -INF) {
            int c = tree[rt].tag;
            tree[lson].tag = tree[rson].tag = c;
            tree[lson].sum = c * tree[lson].Range();
            tree[rson].sum = c * tree[rson].Range();
            if(c >= 0) {
                tree[lson].take(tree[lson].sum);
                tree[rson].take(tree[rson].sum);
            } else {
                tree[lson].take(c);
                tree[rson].take(c);
            }
            tree[rt].tag = -INF;
        }
    }
    void Build(int rt, int l, int r, int val[], int fp[]) {
        tree[rt].l = l, tree[rt].r = r;
        tree[rt].tag = -INF;
        if(l == r) {
            tree[rt].sum = val[fp[l]];
            tree[rt].take(tree[rt].sum);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid, val, fp);
        Build(rson, mid+1, r, val, fp);
        PushUp(tree[rt], tree[lson], tree[rson]);
    }
    void Modify(int rt, int x, int y, int v) {
        if(x <= tree[rt].l && tree[rt].r <= y) {
            tree[rt].tag = v;
            tree[rt].sum = v * tree[rt].Range();
            if(v >= 0) {
                tree[rt].take(tree[rt].sum);
            } else {
                tree[rt].take(v);
            }
            return ;
        }
        PushDown(rt);
        int mid = tree[rt].Mid();
        if(x <= mid)
            Modify(lson, x, y, v);
        if(mid < y)
            Modify(rson, x, y, v);
        PushUp(tree[rt], tree[lson], tree[rson]);
    }
    Node Query(int rt, int x, int y) {
        if(x <= tree[rt].l && tree[rt].r <= y) {
            return tree[rt];
        }
        PushDown(rt);
        int mid = tree[rt].Mid();
        if(y <= mid) {
            return Query(lson, x, y);
        } else if(x > mid) {
            return Query(rson, x, y);
        } else {
            return Merge(Query(lson, x, mid), Query(rson, mid+1, y));
        }
    }
};

class HeavyLightDecompose {
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
    int node_val[MAXN];
    SegmentTree st;

    void Init() {
        tot = pos = 0;
        memset(head, -1, sizeof(head));
        memset(son, -1, sizeof(son));
    }
    void Build(int n) {
        dfs1(1, 1, 1);
        dfs2(1, 1);
        st.Build(1, 1, n, node_val, fp);
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
        p[u] = ++pos;
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
    void Change(int u, int v, int c) {
        int f1 = top[u], f2 = top[v];
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            st.Modify(1, p[f1], p[u], c);
            u = fa[f1];
            f1 = top[u];
        }
        if(deep[u] > deep[v]) swap(u, v);
        st.Modify(1, p[u], p[v], c);
    }
    int GetMax(int u, int v) {
        int f1 = top[u], f2 = top[v];
        SegmentTree::Node q, lc, rc;
        lc.sum = rc.sum = -INF;
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                q = st.Query(1, p[f2], p[v]);
                rc = st.Merge(q, rc);
                v = fa[f2];
                f2 = top[v];
            } else {
                q = st.Query(1, p[f1], p[u]);
                swap(q.lmax, q.rmax);
                lc = st.Merge(lc, q);
                u = fa[f1];
                f1 = top[u];
            }

        }
        if(deep[u] > deep[v]) {
            q = st.Query(1, p[v], p[u]);
            swap(q.lmax, q.rmax);
            lc = st.Merge(lc, q);
        } else {
            q = st.Query(1, p[u], p[v]);
            rc = st.Merge(q, rc);
        }
        q = st.Merge(lc, rc);
        return max(0, q.smax);
    }
};

HeavyLightDecompose hld;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        hld.Init();
        for(int i = 1; i <= n; ++i) {
            hld.node_val[i] = nextInt();
        }
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            hld.AddEdge(u, v);
            hld.AddEdge(v, u);
        }
        hld.Build(n);
        int Q = nextInt();
        while(Q--) {
            int op = nextInt();
            if(op == 1) {
                int a = nextInt();
                int b = nextInt();
                printf("%d\n", hld.GetMax(a, b));
            } else if(op == 2) {
                int a = nextInt();
                int b = nextInt();
                int c = nextInt();
                hld.Change(a, b, c);
            }
        }
    }
    return 0;
}

/*
** HDU 5029 Relief grain
** Created by Rayn @@ 2014/09/23
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstdlib>
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
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-')
    {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
    return ret;
}

const int MAXN = 100010;
const int MAXZ = 100000;
const int INF = 0x3F3F3F3F;

class SegmentTree {
public:
    struct Node
    {
        int l, r;
        int maxt, id;
        inline int Mid() {
            return (l + r) >> 1;
        }
    };
    Node tree[MAXN<<2];

    void PushUp(int rt)
    {
        if(tree[lson].maxt < tree[rson].maxt) {
            tree[rt].id = tree[rson].id;
            tree[rt].maxt = tree[rson].maxt;
        } else {
            tree[rt].id = tree[lson].id;
            tree[rt].maxt = tree[lson].maxt;
        }
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].l = l, tree[rt].r = r;
        if(l == r) {
            tree[rt].id = l;
            tree[rt].maxt = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        PushUp(rt);
    }
    void Update(int rt, int pos, int v)
    {
        if(tree[rt].l == pos && tree[rt].r == pos) {
            tree[rt].maxt += v;
            return ;
        }
        int mid = tree[rt].Mid();
        if(pos <= mid)
            Update(lson, pos, v);
        else
            Update(rson, pos, v);
        PushUp(rt);
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
    vector<int> left_tag[MAXN];
    vector<int> right_tag[MAXN];

    void Init()
    {
        tot = 0;
        pos = 1;
        memset(head, -1, sizeof(head));
        memset(son, -1, sizeof(son));
        for(int i = 1; i <= MAXZ; ++i) {
            left_tag[i].clear();
            right_tag[i].clear();
        }
    }
    void Build()
    {
        dfs1(1, 0, 0);
        dfs2(1, 1);
    }
    void AddEdge(int u, int v)
    {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void dfs1(int u, int pre, int d)
    {
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
    void dfs2(int u, int tp)
    {
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
    void Change(int u, int v, int z)
    {
        int f1 = top[u], f2 = top[v];
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            left_tag[p[f1]].push_back(z);
            right_tag[p[u]+1].push_back(z);
            u = fa[f1];
            f1 = top[u];
        }
        if(deep[u] > deep[v]) swap(u, v);
        left_tag[p[u]].push_back(z);
        right_tag[p[v]+1].push_back(z);
    }
};

HeavyLightDecompose hld;
SegmentTree st;
vector<int> res;
vector<int>::iterator it;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0) break ;
        hld.Init();
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            hld.AddEdge(u, v);
            hld.AddEdge(v, u);
        }
        hld.Build();
        while(m--) {
            int u = nextInt();
            int v = nextInt();
            int z = nextInt();
            hld.Change(u, v, z);
        }
        res.resize(n+1);
        st.Build(1, 1, MAXZ);
        for(int i = 1; i < hld.pos; ++i) {
            it = hld.left_tag[i].begin();
            for(; it != hld.left_tag[i].end(); ++it) {
                st.Update(1, *it, 1);
            }
            it = hld.right_tag[i].begin();
            for(; it != hld.right_tag[i].end(); ++it) {
                st.Update(1, *it, -1);
            }
            int u = hld.fp[i];
            if(st.tree[1].maxt == 0) {
                res[u] = 0;
            } else {
                res[u] = st.tree[1].id;
            }
        }
        for(int i = 1; i <= n; ++i) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}

/*
** HDU 4757 Tree
** Created by Rayn @@ 2014/11/07
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
typedef long long Long;

inline int nextInt() {
    char ch = getchar();
    bool flag = false;
    while ((ch < '0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while (ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if (flag) ret = -ret;
    return ret;
}

const int MAXN = 100010;
const int MAXNODE = MAXN * 20;

struct Edge {
    int u, v, next;
    Edge() {}
    Edge(int u, int v, int next) : u(u), v(v), next(next) {}
};

Edge edge[MAXN << 1];
int nEdge, head[MAXN];
int fa[MAXN], value[MAXN];

struct HLD {
    int pos, top[MAXN], deep[MAXN];
    int sz[MAXN], son[MAXN], p[MAXN];

    void Init(int n) {
        nEdge = pos = 0;
        fill_n(head, n + 3, -1);
        fill_n(son, n + 3, -1);
    }
    void AddEdge(int u, int v) {
        edge[nEdge] = Edge(u, v, head[u]);
        head[u] = nEdge++;
    }
    void dfs(int u, int pre, int dep) {
        deep[u] = dep, fa[u] = pre, sz[u] = 1;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (v != pre) {
                dfs(v, u, dep + 1);
                sz[u] += sz[v];
                if (son[u] == -1 || sz[v] > sz[son[u]]) {
                    son[u] = v;
                }
            }
        }
    }
    void Decompose(int u, int tp) {
        top[u] = tp;
        p[u] = ++pos;
        if (son[u] == -1) return;
        Decompose(son[u], tp);
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (v != son[u] && v != fa[u]) {
                Decompose(v, v);
            }
        }
    }
    void Build() {
        dfs(1, 0, 0);
        Decompose(1, 1);
    }
    int GetLCA(int u, int v) {
        int f1 = top[u], f2 = top[v];
        while (f1 != f2) {
            if (deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            u = fa[f1];
            f1 = top[u];
        }
        if (deep[u] > deep[v]) swap(u, v);
        return u;
    }
};

struct TrieNode {
    int cnt;
    int ch[2];
    TrieNode() {
        cnt = ch[0] = ch[1] = 0;
    }
};

struct Trie {
    TrieNode pool[MAXNODE];
    int sz, root[MAXN];

    void Init() {
        sz = 1;
        root[0] = pool[0].cnt = 0;
        memset(pool[0].ch, 0, sizeof(pool[0].ch));
    }
    void Build(int u) {
        root[u] = Insert(root[fa[u]], value[u]);
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (v == fa[u]) continue;
            Build(v);
        }
    }
    int Insert(int fa, int w) {
        int rt = sz++;
        int cur = rt;
        pool[cur] = pool[fa];
        for (int i = 15; i >= 0; --i) {
            int v = (w >> i) & 1;
            int next = sz++;
            pool[next] = pool[pool[cur].ch[v]];
            pool[next].cnt++;
            pool[cur].ch[v] = next;
            cur = next;
        }
        return rt;
    }
    int Query(int rtx, int rty, int lca, int w) {
        int ret = value[lca] ^ w, ans = 0;
        int rtz = root[lca];
        for (int i = 15; i >= 0; --i) {
            int v = ((w >> i) & 1) ^ 1;
            int cnt = pool[pool[rtx].ch[v]].cnt + pool[pool[rty].ch[v]].cnt - 2 * pool[pool[rtz].ch[v]].cnt;
            if (cnt) {
                ans |= (1 << i);
            } else {
                v = v ^ 1;
            }
            rtx = pool[rtx].ch[v];
            rty = pool[rty].ch[v];
            rtz = pool[rtz].ch[v];
        }
        ret = max(ret, ans);
        return ret;
    }
    int Gao(int u, int v, int lca, int w) {
        return Query(root[u], root[v], lca, w);
    }
};

Trie trie;
HLD tree;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            value[i] = nextInt();
        }
        tree.Init(n);
        for (int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            tree.AddEdge(u, v);
            tree.AddEdge(v, u);
        }
        tree.Build();
        trie.Init();
        trie.Build(1);
        while (m--) {
            int u = nextInt();
            int v = nextInt();
            int w = nextInt();
            printf("%d\n", trie.Gao(u, v, tree.GetLCA(u, v), w));
        }
    }
    return 0;
}

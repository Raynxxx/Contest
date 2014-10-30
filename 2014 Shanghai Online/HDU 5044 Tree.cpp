/*
** HDU 5044 Tree
** Created by Rayn @@ 2014/09/27
*/
#pragma comment(linker, "/STACK:102400000,102400000")
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
typedef pair<int, int> PII;
typedef long long LL;

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    if(ch == EOF) return 0;
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
template <typename T>
inline void print(T x)
{
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x >= 10) {
        print(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

PII pool[MAXN];
int link[MAXN];
LL node_val[MAXN];
LL edge_val[MAXN];

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
    LL node_tag[MAXN];
    LL edge_tag[MAXN];

    void Init() {
        tot = pos = 0;
        memset(head, -1, sizeof(head));
        memset(son, -1, sizeof(son));
        memset(node_tag, 0, sizeof(node_tag));
        memset(edge_tag, 0, sizeof(edge_tag));
    }
    void Build(int n) {
        dfs1(1, 0, 0);
        dfs2(1, 1);
        for(int i = 1; i < n; ++i) {
            if(deep[pool[i].first] > deep[pool[i].second]) {
                swap(pool[i].first, pool[i].second);
            }
            link[pool[i].second] = i;
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
    void ADD1(int u, int v, int w) {
        int f1 = top[u], f2 = top[v];
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            node_tag[p[f1]] += w;
            node_tag[p[u]+1] -= w;
            u = fa[f1];
            f1 = top[u];
        }
        if(deep[u] > deep[v]) swap(u, v);
        node_tag[p[u]] += w;
        node_tag[p[v]+1] -= w;
    }
    void ADD2(int u, int v, int w) {
        int f1 = top[u], f2 = top[v];
        while(f1 != f2) {
            if(deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            edge_tag[p[f1]] += w;
            edge_tag[p[u]+1] -= w;
            u = fa[f1];
            f1 = top[u];
        }
        if(u == v) return;
        if(deep[u] > deep[v]) swap(u, v);
        edge_tag[p[son[u]]] += w;
        edge_tag[p[v]+1] -= w;
    }
    void Gao(int n) {
        for(int i = 1; i <= n; ++i) {
            node_tag[i] += node_tag[i-1];
            node_val[fp[i]] = node_tag[i];
            edge_tag[i] += edge_tag[i-1];
            edge_val[link[fp[i]]] = edge_tag[i];
        }
    }
};

HeavyLightDecompose hld;

int main()
{
    int __size__ = 256 << 20;
    char * __p__ = (char *) malloc(__size__) + __size__;
    __asm__("movl %0, %%esp\n"::"r"(__p__));
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        hld.Init();
        int n = nextInt();
        int m = nextInt();
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            hld.AddEdge(u, v);
            hld.AddEdge(v, u);
            pool[i] = make_pair(u, v);
        }
        hld.Build(n);
        while(m--) {
            char op[10];
            scanf("%s", op);
            int u = nextInt();
            int v = nextInt();
            int k = nextInt();
            if(op[3] == '1') {
                hld.ADD1(u, v, k);
            } else{
                hld.ADD2(u, v, k);
            }
        }
        printf("Case #%d:\n", ++cases);
        hld.Gao(n);
        for(int i = 1; i <= n; ++i) {
            print(node_val[i]);
            if(i < n) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
        for (int i = 1; i < n; ++i) {
            print(edge_val[i]);
            if(i < n-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}

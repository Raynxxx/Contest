/*
** SPOJ Query on a tree (Link-Cut-Tree)
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

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int key;
    int maxv;

    inline void PushUp() {
        if(this == null) return ;
        maxv = max(key, max(ch[0]->maxv, ch[1]->maxv));
    }
    inline void setChild(Node *p, int d) {
        ch[d] = p;
        p->fa = this;
    }
    inline bool isRight() {
        return fa->ch[1] == this;
    }
    inline bool isRoot() {
        return fa == null || fa->ch[0] != this && fa->ch[1] != this;
    }
    inline void Rotate() {
        Node *f = fa, *ff = fa->fa;
        int c = isRight(), cc = fa->isRight();
        f->setChild(ch[!c], c);
        this->setChild(f, !c);
        if(ff->ch[cc] == f) {
            ff->setChild(this, cc);
        } else {
            this->fa = ff;
        }
        f->PushUp();
    }
    inline Node* Splay() {
        while(!isRoot()) {
            if(!fa->isRoot()) {
                (isRight() == fa->isRight())? fa->Rotate() : Rotate();
            }
            Rotate();
        }
        PushUp();
        return this;
    }
    inline Node* Access() {
        for(Node *p = this, *q = null; p != null; q = p, p = p->fa) {
            p->Splay()->setChild(q, 1);
            p->PushUp();
        }
        return Splay();
    }
};

class LinkCutTree {
public:
    struct Edge {
        int v, next;
        int w, id;
        Edge() {}
        Edge(int v, int w, int id, int next): v(v), w(w), id(id), next(next) {}
    };

    Node pool[MAXN], *tail;
    Node *node[MAXN];
    Node *tree[MAXN];
    Edge edge[MAXN<<1];
    int tot, head[MAXN];
    bool vis[MAXN];

    void Init(int n) {
        tot = 0;
        fill(head, head + 1 + n, -1);
        tail = pool;
        null = tail++;
        null->fa = null->ch[0] = null->ch[1] = null;
        null->maxv = null->key = 0;
        for(int i = 1; i <= n; ++i) {
            node[i] = tail++;
            node[i]->fa = node[i]->ch[0] = node[i]->ch[1] = null;
            node[i]->maxv = node[i]->key = 0;
        }
    }
    void AddEdge(int u, int v, int w, int id) {
        edge[tot] = Edge(v, w, id, head[u]);
        head[u] = tot++;
    }
    void Build(int n) {
        fill(vis, vis + 1 + n, false);
        queue<int> que;
        que.push(1);
        vis[1] = true;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].v;
                if(vis[v]) continue;
                vis[v] = true;
                que.push(v);
                tree[edge[i].id] = node[v];
                node[v]->key = edge[i].w;
                node[v]->PushUp();
                node[v]->fa = node[u];
            }
        }
    }
    int Query(Node *x, Node *y) {
        x->Access();
        for(x = null; y != null; x = y, y = y->fa) {
            y->Splay();
            if(y->fa == null) {
                return max(y->ch[1]->maxv, x->maxv);
            }
            y->setChild(x, 1);
            y->PushUp();
        }
    }
    void Modify(int id, int v) {
        tree[id]->Splay()->key = v;
        tree[id]->PushUp();
    }
    int GetMax(int u, int v) {
        return Query(node[u], node[v]);
    }
};

LinkCutTree lct;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n = nextInt();
        lct.Init(n);
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            int w = nextInt();
            lct.AddEdge(u, v, w, i);
            lct.AddEdge(v, u, w, i);
        }
        lct.Build(n);
        char op[20];
        while(scanf("%s", op) && op[0] != 'D') {
            int x = nextInt();
            int y = nextInt();
            if(op[0] == 'C') {
                lct.Modify(x, y);
            } else if(op[0] == 'Q') {
                printf("%d\n", lct.GetMax(x, y));
            }
        }
    }
    return 0;
}

/*
** SPOJ Query on a tree again
** Created by Rayn @@ 2014/09/29
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
template <typename T>
inline void write(T x)
{
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x >= 10) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int id;
    int val;
    int cnt;

    inline void InitNode() {
        fa = ch[0] = ch[1] = null;
        val = cnt = 0;
    }
    inline void PushUp() {
        if(this == null) return ;
        cnt = val + ch[0]->cnt + ch[1]->cnt;
    }
    inline void setChild(Node *p, int d) {
        ch[d] = p;
        p->fa = this;
    }
    inline bool isRight() {
        return fa->ch[1] == this;
    }
    inline bool isRoot() {
        return fa == null || (fa->ch[0] != this && fa->ch[1] != this);
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
        int to, next;
        Edge() {}
        Edge(int to, int next): to(to), next(next) {}
    };

    Node pool[MAXN], *tail;
    Node *node[MAXN];
    Edge edge[MAXN<<1];
    int tot, head[MAXN];

    void AddEdge(int u, int v)
    {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void Init(int n)
    {
        tot = 0;
        memset(head, -1, sizeof(head));
        tail = pool;
        null = tail++;
        null->InitNode();
        for(int i = 1; i <= n; ++i) {
            node[i] = tail++;
            node[i]->id = i;
            node[i]->InitNode();
        }
    }
    void Build(int u, int pre)
    {
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(v == pre) continue;
            Build(v, u);
            node[v]->fa = node[u];
        }
    }
    void Change(int index)
    {
        node[index]->Splay()->val ^= 1;
        node[index]->PushUp();
    }
    int Ask(int v)
    {
        node[v]->Access();
        if(node[v]->cnt == 0) return -1;
        Node *x = node[v];
        while(x != null) {
            if(x->ch[0]->cnt == 0 && x->val == 1) {
                return x->id;
            } else if(x->ch[0]->cnt) {
                x = x->ch[0];
            } else {
                x = x->ch[1];
            }
        }
    }
};

LinkCutTree lct;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        lct.Init(n);
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            lct.AddEdge(u, v);
            lct.AddEdge(v, u);
        }
        lct.Build(1, 1);
        while(m--) {
            int op = nextInt();
            if(op == 0) {
                int index = nextInt();
                lct.Change(index);
            } else {
                int v = nextInt();
                printf("%d\n", lct.Ask(v));
            }
        }
    }
    return 0;
}

/*
** HDU 4010 Query on The Trees
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

const int MAXN = 300000 + 10;
const int INF = 0x3F3F3F3F;

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int key;
    int maxv;
    int add;
    bool flip;

    inline void Update_Add(int d) {
        if(this == null) return ;
        key += d;
        add += d;
        maxv += d;
    }
    inline void Reverse() {
        if(this == null) return ;
        swap(ch[0], ch[1]);
        flip ^= 1;
    }
    inline void PushUp() {
        maxv = max(key, max(ch[0]->maxv, ch[1]->maxv));
    }
    inline void PushDown() {
        if(add) {
            ch[0]->Update_Add(add);
            ch[1]->Update_Add(add);
            add = 0;
        }
        if(flip) {
            ch[0]->Reverse();
            ch[1]->Reverse();
            flip = 0;
        }
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
    inline void Fix() {
        if(!isRoot()) fa->Fix();
        PushDown();
    }
    inline Node* Splay() {
        Fix();
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
    inline void MakeRoot() {
        Access()->Reverse();
    }
    inline Node* FindRoot() {
        Node *x;
        for(x = Access(); x->PushDown(), x->ch[0] != null; x = x->ch[0]);
        return x;
    }
    inline void cut() {
        Access();
        ch[0]->fa = null;
        ch[0] = null;
        PushUp();
    }
    inline bool Cut(Node *x) {
        if(this == x || FindRoot() != x->FindRoot()) return false;
        x->MakeRoot();
        cut();
        return true;
    }
    inline bool Link(Node *x) {
        if(FindRoot() == x->FindRoot()) return false;
        MakeRoot();
        fa = x;
        return true;
    }
};

class LinkCutTree {
public:
    struct Edge {
        int v, next;
        Edge() {}
        Edge(int v, int next):
            v(v), next(next) {}
    };

    Node pool[MAXN], *tail;
    Node *node[MAXN];
    Edge edge[MAXN<<1];
    int tot, head[MAXN];

    void Init(int n) {
        tot = 0;
        fill(head, head + 1 + n, -1);
        tail = pool;
        null = tail++;
        null->fa = null->ch[0] = null->ch[1] = null;
        null->key = null->maxv = 0;
        null->flip = null->add = 0;
        for(int i = 1; i <= n; ++i) {
            node[i] = tail++;
            node[i]->fa = node[i]->ch[0] = node[i]->ch[1] = null;
            node[i]->key = node[i]->maxv = 0;
            node[i]->flip = node[i]->add = 0;
        }
    }
    void AddEdge(int u, int v) {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void Build(int u, int pre) {
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if(v == pre) continue;
            Build(v, u);
            node[v]->fa = node[u];
        }
    }
    void ADD(Node *x, Node *y, int w) {
        if(x->FindRoot() != y->FindRoot()) {
            puts("-1");
            return ;
        }
        x->Access();
        for(x = null; y != null; x = y, y = y->fa) {
            y->Splay();
            if(y->fa == null) {
                y->ch[1]->Update_Add(w);
                x->Update_Add(w);
                y->key += w;
                y->PushUp();
                return ;
            }
            y->setChild(x, 1);
            y->PushUp();
        }
    }
    int getMax(Node *x, Node *y) {
        if(x->FindRoot() != y->FindRoot()) return -1;
        x->Access();
        for(x = null; y != null; x = y, y = y->fa) {
            y->Splay();
            if(y->fa == null) {
                return max(y->key, max(y->ch[1]->maxv, x->maxv));
            }
            y->setChild(x, 1);
            y->PushUp();
        }
    }
    void Link(int x, int y) {
        if(!node[x]->Link(node[y])) {
            puts("-1");
        }
    }
    void Cut(int x, int y) {
        if(!node[y]->Cut(node[x])) {
            puts("-1");
        }
    }
    void AddWeight(int x, int y, int w) {
        ADD(node[x], node[y], w);
    }
    void Query(int x, int y) {
        printf("%d\n", getMax(node[x], node[y]));
    }
    void Debug(int n) {
        for(int i = 1; i <= n; ++i) {
            printf("%d ", node[i]->key);
        }
        printf("\n");
    }
};

LinkCutTree lct;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        lct.Init(n);
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            lct.AddEdge(u, v);
            lct.AddEdge(v, u);
        }
        lct.Build(1, 1);
        for(int i = 1; i <= n; ++i) {
            lct.node[i]->key = nextInt();
            lct.node[i]->maxv = lct.node[i]->key;
        }
        int Q = nextInt();
        while(Q--) {
            int op = nextInt();
            if(op == 1) {
                int x = nextInt();
                int y = nextInt();
                lct.Link(x, y);
            } else if(op == 2) {
                int x = nextInt();
                int y = nextInt();
                lct.Cut(x, y);
            } else if(op == 3) {
                int w = nextInt();
                int x = nextInt();
                int y = nextInt();
                lct.AddWeight(x, y, w);
            } else if(op == 4) {
                int x = nextInt();
                int y = nextInt();
                lct.Query(x, y);
            }
            //lct.Debug(n);
        }
        printf("\n");
    }
    return 0;
}

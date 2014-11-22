/*
** SPOJ Query on a tree II
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

const int MAXN = 10010;
const int INF = 0x3F3F3F3F;

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int sz;
    int val;
    int sum;
    int id;

    inline void InitNode(const int& v) {
        fa = ch[0] = ch[1] = null;
        sum = val = v;
        sz = 1;
    }
    inline void PushUp() {
        if(this == null) return ;
        sz = 1 + ch[0]->sz + ch[1]->sz;
        sum = val + ch[0]->sum + ch[1]->sum;
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
        int to, w, next;
        Edge() {}
        Edge(int to, int w, int next): to(to), w(w), next(next) {}
    };

    Node pool[MAXN], *tail;
    Node *node[MAXN];
    Edge edge[MAXN<<1];
    int tot, head[MAXN];

    void AddEdge(int u, int v, int w)
    {
        edge[tot] = Edge(v, w, head[u]);
        head[u] = tot++;
    }
    void Init(int n)
    {
        tot = 0;
        memset(head, -1, sizeof(head));
        tail = pool;
        null = tail++;
        null->InitNode(0);
        null->sz = null->id = 0;
        for(int i = 1; i <= n; ++i) {
            node[i] = tail++;
            node[i]->id = i;
            node[i]->InitNode(0);
        }
    }
    void Build(int u, int pre)
    {
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(v == pre) continue;
            Build(v, u);
            node[v]->val = edge[i].w;
            node[v]->PushUp();
            node[v]->fa = node[u];
        }
    }
    Node* GetKthNode(Node *r, int k)
    {
        Node *x = r;
        while(x->ch[0]->sz + 1 != k) {
            if(k < x->ch[0]->sz + 1) {
                x = x->ch[0];
            } else {
                k -= x->ch[0]->sz + 1;
                x = x->ch[1];
            }
        }
        return x;
    }
    int QuerySum(Node *x, Node *y)
    {
        x->Access();
        for(x = null; y != null; x = y, y = y->fa) {
            y->Splay();
            if(y->fa == null) {
                //printf("%d -> %d -> %d -> %d -> %d\n", y->ch[1]->ch[1]->id, y->ch[1]->id, y->id, x->id, x->ch[1]->id);
                //printf("   %d -> %d -> %d -> %d\n", y->ch[1]->ch[1]->val, y->ch[1]->val, x->val, x->ch[1]->val);
                return y->ch[1]->sum + x->sum;
            }
            y->setChild(x, 1);
            y->PushUp();
        }
    }
    int QueryKth(Node *x, Node *y, int k)
    {
        x->Access();
        for(x = null; y != null; x = y, y = y->fa) {
            y->Splay();
            if(y->fa == null) {
                if(y->ch[1]->sz + 1 == k) {
                    return y->id;
                } else if(y->ch[1]->sz + 1 > k) {
                    return GetKthNode(y->ch[1], y->ch[1]->sz + 1 - k)->id;
                } else {
                    return GetKthNode(x, k - (y->ch[1]->sz + 1))->id;
                }
            }
            y->setChild(x, 1);
            y->PushUp();
        }
    }
    int DIST(int a, int b)
    {
        return QuerySum(node[a], node[b]);
    }
    int KTH(int a, int b, int k)
    {
        return QueryKth(node[a], node[b], k);
    }
};

LinkCutTree lct;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    T = nextInt();
    while(T--)
    {
        int n = nextInt();
        lct.Init(n);
        for(int i = 1; i < n; ++i) {
            int a = nextInt();
            int b = nextInt();
            int w = nextInt();
            lct.AddEdge(a, b, w);
            lct.AddEdge(b, a, w);
        }
        lct.Build(1, 1);
        char op[10];
        while(scanf("%s", op) == 1) {
            if(strcmp(op, "DONE") == 0) break;
            if(strcmp(op, "DIST") == 0) {
                int a = nextInt();
                int b = nextInt();
                write(lct.DIST(a, b));
                printf("\n");
            } else if(strcmp(op, "KTH") == 0) {
                int a = nextInt();
                int b = nextInt();
                int k = nextInt();
                write(lct.KTH(a, b, k));
                printf("\n");
            }
        }
    }
    return 0;
}

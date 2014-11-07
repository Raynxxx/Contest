/*
** HDU 5052 Yaoge's maximum profit
** Created by Rayn @@ 2014/09/27
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

const int MAXN = 50010;
const int INF = 0x3F3F3F3F;

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int val;
    int maxv;
    int minv;
    int lm;
    int rm;
    int add;
    bool flip;

    inline void Set(const int& v) {
        fa = ch[0] = ch[1] = null;
        val = maxv = minv = v;
        flip = add = lm = rm = 0;
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
    inline void PushUp() {
        if(this == null) return;
        lm = max(0, max(ch[0]->lm, ch[1]->lm));
        lm = max(lm, max(val, ch[1]->maxv) - ch[0]->minv);
        lm = max(lm, ch[1]->maxv - min(val, ch[0]->minv));
        rm = max(0, max(ch[0]->rm, ch[1]->rm));
        rm = max(rm, max(val, ch[0]->maxv) - ch[1]->minv);
        rm = max(rm, ch[0]->maxv - min(val, ch[1]->minv));
        maxv = max(val, max(ch[0]->maxv, ch[1]->maxv));
        minv = min(val, min(ch[0]->minv, ch[1]->minv));
    }
    inline void Reverse() {
        if(this == null) return;
        swap(ch[0], ch[1]);
        swap(lm, rm);
        flip ^= 1;
    }
    inline void UpdateAdd(int w) {
        if(this == null) return;
        val += w;
        add += w;
        maxv += w;
        minv += w;
    }
    inline void PushDown() {
        if(this == null) return ;
        if(flip) {
            ch[0]->Reverse();
            ch[1]->Reverse();
            flip = 0;
        }
        if(add) {
            ch[0]->UpdateAdd(add);
            ch[1]->UpdateAdd(add);
            add = 0;
        }
    }
    inline void Fix() {
        if(!isRoot()) fa->Fix();
        PushDown();
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
        Node *p = this, *q = null;
        for(; p != null; q = p, p = p->fa) {
            p->Splay()->setChild(q, 1);
            p->PushUp();
        }
        return Splay();
    }
    inline void MakeRoot() {
        Access()->Reverse();
    }
};

class LinkCutTree {
public:
    struct Edge {
        int to, next;
        Edge() {}
        Edge(int to, int next): to(to), next(next) {}
    };

    Edge edge[MAXN<<1];
    int tot, head[MAXN];

    Node pool[MAXN], *tail;
    Node *node[MAXN];
    int fa[MAXN];

    void Init() {
        tot = 0;
        memset(head, -1, sizeof(head));
        tail = pool;
        null = tail++;
        null->fa = null->ch[0] = null->ch[1] = null;
        null->maxv = -INF;
        null->minv = INF;
        null->lm = null->add = null->flip = 0;
    }
    void CreateNode(int n) {
        for(int i = 1; i <= n; ++i) {
            int w = nextInt();
            node[i] = tail++;
            node[i]->Set(w);
        }
    }
    void AddEdge(int u, int v) {
        edge[tot] = Edge(v, head[u]);
        head[u] = tot++;
    }
    void Build() {
        queue<int> que;
        que.push(1);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if(v == fa[u]) continue;
                fa[v] = u;
                node[v]->fa = node[u];
                que.push(v);
            }
        }
    }
    int Gao(int x, int y, int v) {
        node[x]->MakeRoot();
        node[y]->Access();
        int ret = node[y]->lm;
        node[y]->UpdateAdd(v);
        return ret;
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
    while(T--) {
        int n = nextInt();
        lct.Init();
        lct.CreateNode(n);
        for(int i = 1; i < n; ++i) {
            int u = nextInt();
            int v = nextInt();
            lct.AddEdge(u, v);
            lct.AddEdge(v, u);
        }
        lct.Build();
        int Q = nextInt();
        while(Q--) {
            int x = nextInt();
            int y = nextInt();
            int v = nextInt();
            write(lct.Gao(x, y, v));
            printf("\n");
        }
    }
    return 0;
}

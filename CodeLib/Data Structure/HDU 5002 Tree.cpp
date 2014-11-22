/*
** HDU 5002 Tree
** Created by Rayn @@ 2014/09/14
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAXN = 100010;

struct Node
{
    Node *pa, *ch[2];
    bool flip, flag;
    int val;
    int sz;
    int max1, sum1;
    int max2, sum2;
    int add;
    int change;

    void Init(int v)
    {
        val = max1 = v;
        sum1 = sz = 1;
        max2 = -INF;
        sum2 = add = 0;
        flag = flip = false;
        pa = ch[0] = ch[1] = NULL;
    }

    void Update(Node* t)
    {
        bool f = false;
        if(t->max1 > max1) {
            max2 = max1;
            sum2 = sum1;
            max1 = t->max1;
            sum1 = t->sum1;
            f = true;
        } else if(t->max1 == max1) {
            sum1 += t->sum1;
            f = true;
        } else {
            if(t->max1 > max2) {
                max2 = t->max1;
                sum2 = t->sum1;
            } else if(t->max1 == max2) {
                sum2 += t->sum1;
            }
        }
        if(f) {
            if(t->max2 > max2) {
                max2 = t->max2;
                sum2 = t->sum2;
            } else if(t->max2 == max2) {
                sum2 += t->sum2;
            }
        }
    }

    void PushDown()
    {
        if(flip) {
            swap(ch[0], ch[1]);
            if(ch[0]) ch[0]->flip ^= 1;
            if(ch[1]) ch[1]->flip ^= 1;
            flip = false;
        }
        if(flag) {
            val = max1 = change;
            sum1 = sz;
            max2 = -INF;
            sum2 = 0;
            if(ch[0]) {
                ch[0]->flag = true;
                ch[0]->change = change;
                ch[0]->add = 0;
            }
            if(ch[1]) {
                ch[1]->flag = true;
                ch[1]->change = change;
                ch[1]->add = 0;
            }
            flag = false;
        }
        if(add) {
            max1 += add;
            val += add;
            if(max2 != -INF) max2 += add;
            if(ch[0]) ch[0]->add += add;
            if(ch[1]) ch[1]->add += add;
            add = 0;
        }
    }
    void PushUp()
    {
        max1 = val;
        sum1 = 1;
        max2 = -INF;
        sum2 = 0;
        sz = 1;
        if(ch[0]) {
            sz += ch[0]->sz;
            ch[0]->PushDown();
            Update(ch[0]);
        }
        if(ch[1]) {
            sz += ch[1]->sz;
            ch[1]->PushDown();
            Update(ch[1]);
        }
    }
};

Node *c[MAXN], pool[MAXN];

void Rotate(Node *o, int d)
{
    Node *x = o->pa, *y = x->pa;
    o->pa = y;
    if(y && (y->ch[0] == x || y->ch[1] == x)) {
        if(y->ch[0] == x)
            y->ch[0] = o;
        else
            y->ch[1] = o;
    }
    y = o->ch[d^1];
    if(y) y->pa = x;
    x->ch[d] = y;
    x->pa = o;
    x->PushUp();
    o->ch[d^1] = x;
}
void Splay(Node* o)
{
    o->PushDown();
    while(o->pa && (o->pa->ch[0] == o || o->pa->ch[1] == o)) {
        Node *x = o->pa, *y = x->pa;
        if(y && (y->ch[0] == x || y->ch[1] == x)) {
            y->PushDown();
            x->PushDown();
            o->PushDown();
            if(y->ch[0] == x && x->ch[0] == o) {
                Rotate(x, 0);
            } else if(y->ch[1] == x && x->ch[1] == o) {
                Rotate(x, 1);
            } else if(x->ch[0] == o) {
                Rotate(o, 0);
            } else {
                Rotate(o, 1);
            }
        } else {
            x->PushDown();
            o->PushDown();
        }
        if(o->pa->ch[0] == o) {
            Rotate(o, 0);
        } else {
            Rotate(o, 1);
        }
    }
    o->PushUp();
}
Node* Expose(Node *o)
{
    Node* k;
    for(k = NULL; o; o = o->pa) {
        Splay(o);
        o->ch[1] = k;
        k = o;
        k->PushUp();
    }
    return k;
}
void Split(int x, int y)
{
    Expose(c[x]);
    Node* u = Expose(c[y]);
    Splay(c[x]);
    if(u == c[x]) {
        c[y]->pa = NULL;
        c[x]->ch[1] = NULL;
        c[x]->PushUp();
    }
    if(u == c[y]) {
        c[x]->pa = NULL;
    }
}
void Link(int x, int y)
{
    Expose(c[x]);
    Expose(c[y]);
    Splay(c[x]);
    Splay(c[y]);
    c[x]->flip ^= 1;
    c[x]->pa = c[y];
    c[x]->PushDown();
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        printf("Case #%d:\n", ++cases);
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            c[i] = &pool[i];
            c[i]->Init(x);
        }
        for(int i = 0; i < n-1; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            Link(x, y);
        }
        while(m--)
        {
            int op;
            scanf("%d", &op);
            if(op == 1) {
                int x, y, a, b;
                scanf("%d%d%d%d", &x, &y, &a, &b);
                Split(x, y);
                Link(a, b);
            } else if(op == 2) {
                int x, y, d;
                scanf("%d%d%d", &x, &y, &d);
                Expose(c[x]);
                Node *u = Expose(c[y]);
                Splay(u);
                u->val = d;
                if(u->ch[1]) {
                    u->ch[1]->flag = true;
                    u->ch[1]->change = d;
                    u->add = 0;
                    u->ch[1]->PushDown();
                }
                u->PushUp();
                if(u != c[x]) {
                    Splay(c[x]);
                    c[x]->flag = true;
                    c[x]->change = d;
                    c[x]->add = 0;
                    c[x]->PushDown();
                }
            } else if(op == 3) {
                int x, y, d;
                scanf("%d%d%d", &x, &y, &d);
                Expose(c[x]);
                Node *u = Expose(c[y]);
                Splay(u);
                u->val += d;
                if(u->ch[1]) {
                    u->ch[1]->add += d;
                    u->ch[1]->PushDown();
                }
                u->PushUp();
                if(u != c[x]) {
                    Splay(c[x]);
                    c[x]->add += d;
                    c[x]->PushDown();
                }
            } else {
                int x, y;
                scanf("%d%d", &x, &y);
                Expose(c[x]);
                Node *u = Expose(c[y]);
                Splay(u);
                Node *t = &pool[n+1];
                t->Init(u->val);
                if (u->ch[1]) {
                    t->Update(u->ch[1]);
                }
                if (u != c[x]) {
                    Splay(c[x]);
                    t->Update(c[x]);
                }
                if (t->max2 == -INF) {
                    puts("ALL SAME");
                } else {
                    printf("%d %d\n", t->max2, t->sum2);
                }
            }
        }
    }
    return 0;
}

/*
** ZOJ 3765 Lights
** Created by Rayn @@ 2014/09/04
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXL = 200005;
const int MAXN = 300005;
const int INF = 0x3F3F3F3F;

int N, Q;
int num[MAXL], status[MAXL];

int gcd(int a, int b)
{
    if(a == -1) return b;
    else if(b == -1) return a;
    return (b == 0)? a : gcd(b, a%b);
}

class SplayTree
{
public:
    struct Node
    {
        Node* ch[2];
        int val;
        int sz;
        int status;
        int g[2];

        inline void setNode(int v, int s) {
            sz = 1; val = v; status = s;
            g[s] = v; g[s^1] = -1;
        }
        inline int cmp(int k) const {
            int d = k - ch[0]->sz;
            if(d == 1) return -1;
            return (d <= 0)? 0 : 1;
        }
        inline void Flip() {
            status ^= 1;
            PushUp();
        }
        inline void PushUp() {
            sz = ch[0]->sz + ch[1]->sz + 1;
            g[0] = gcd(ch[0]->g[0], ch[1]->g[0]);
            g[1] = gcd(ch[0]->g[1], ch[1]->g[1]);
            g[status] = gcd(g[status], val);
        }
    };

    Node *cur, pool[MAXN];
    Node *root, *null;

    Node* newNode(int v, int s)
    {
        cur->setNode(v, s);
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    void CreateNull()
    {
        null = newNode(-1, 0);
        null->sz = 0;
        null->val = -1;
        null->status = 0;
        null->g[0] = null->g[1] = -1;
    }
    Node* Build(int L, int R)
    {
        if(L > R) return null;
        int M = (L + R) >> 1;
        Node* o = newNode(num[M], status[M]);
        o->ch[0] = Build(L, M-1);
        o->ch[1] = Build(M+1, R);
        o->PushUp();
        return o;
    }
    void Rotate(Node* &o, int d)
    {
        Node* k = o->ch[d^1];
        o->ch[d^1] = k->ch[d];
        k->ch[d] = o;
        o->PushUp();
        k->PushUp();
        o = k;
    }
    void Splay(Node* &o, int k)
    {
        int d = o->cmp(k);
        if(d == 1) {
            k -= o->ch[0]->sz + 1;
        }
        if(d != -1) {
            Node* p = o->ch[d];
            int d2 = p->cmp(k);
            int k2 = (d2 == 0)? k : k - p->ch[0]->sz - 1;
            if(d2 != -1) {
                Splay(p->ch[d2], k2);
                if(d == d2) {
                    Rotate(o, d^1);
                } else {
                    Rotate(o->ch[d], d);
                }
            }
            Rotate(o, d^1);
        }
    }
    Node*& getRange(int L, int R)
    {
        Splay(root, L);
        Splay(root->ch[1], R-L+1);
        return root->ch[1]->ch[0];
    }
    Node* lastRange() const
    {
        return root->ch[1]->ch[0];
    }
    void Update_dummy()
    {
        root->ch[1]->PushUp();
        root->PushUp();
    }

public:
    void Init(int N)
    {
        cur = pool;
        CreateNull();
        root = newNode(-1, 0);
        root->sz = 0;
        root->ch[1] = newNode(-1, 0);
        root->ch[1]->sz = 0;
        root->ch[1]->ch[0] = Build(1, N);
        Update_dummy();
    }
    void Insert(int pos, int val, int s)
    {
        getRange(pos+1, pos+1) = newNode(val, s);
        Update_dummy();
    }
    void Delete(int pos)
    {
        getRange(pos, pos+1) = null;
        Update_dummy();
    }
    void Turn(int pos)
    {
        getRange(pos, pos+1)->Flip();
        Update_dummy();
    }
    void Modify(int pos, int val)
    {
        getRange(pos, pos+1)->val = val;
        lastRange()->PushUp();
        Update_dummy();
    }
    int Query(int L, int R, int s)
    {
        return getRange(L, R+1)->g[s];
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &N, &Q) != EOF)
    {
        for(int i = 1; i <= N; ++i) {
            scanf("%d%d", &num[i], &status[i]);
        }
        Solver.Init(N);
        //printf("%d\n", Solver.root->ch[1]->ch[0]->sz);
        while(Q--)
        {
            char op[2];
            int pos, v, s;
            scanf("%s", op);
            if(op[0] == 'I') {
                scanf("%d%d%d", &pos, &v, &s);
                Solver.Insert(pos, v, s);
            } else if(op[0] == 'D') {
                scanf("%d", &pos);
                Solver.Delete(pos);
            } else if(op[0] == 'R') {
                scanf("%d", &pos);
                Solver.Turn(pos);
            } else if(op[0] == 'M') {
                scanf("%d%d", &pos, &v);
                Solver.Modify(pos, v);
            } else if(op[0] == 'Q') {
                int L, R;
                scanf("%d%d%d", &L, &R, &s);
                printf("%d\n", Solver.Query(L, R, s));
            }
        }
    }
    return 0;
}


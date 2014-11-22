/*
** HDU 3487 Play with Chain
** Created by Rayn @@ 2014/09/07
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 300010;

class SplayTree
{
private:
    struct Node
    {
        Node *ch[2];
        int s;
        int v;
        int flip;

        inline int cmp(int k) const
        {
            int d = k - ch[0]->s;
            if (d == 1) return -1;
            return (d <= 0) ? 0 : 1;
        }
        inline void Flip() {
            flip ^= 1;
            swap(ch[0], ch[1]);
        }
    };

    Node *cur, pool[MAXN];
    Node *root, *null;

    inline void PushUp(Node* o)
    {
        o->s = o->ch[0]->s + o->ch[1]->s + 1;
    }
    inline void PushDown(Node* o)
    {
        if(o->flip) {
            o->flip = 0;
            o->ch[0]->Flip();
            o->ch[1]->Flip();
        }
    }
    inline Node* newNode(int v)
    {
        cur->s = 1;
        cur->flip = 0;
        cur->v = v;
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    void Rotate(Node* &o, int d)
    {
        Node* k = o->ch[d^1];
        o->ch[d^1] = k->ch[d];
        k->ch[d] = o;
        PushUp(o);
        PushUp(k);
        o = k;
    }
    void Splay(Node* &o, int k)
    {
        PushDown(o);
        int d = o->cmp(k);
        if(d == 1) k -= o->ch[0]->s + 1;
        if(d != -1) {
            Node* p = o->ch[d];
            PushDown(p);
            int d2 = p->cmp(k);
            int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
            if (d2 != -1) {
                Splay(p->ch[d2], k2);
                if (d == d2) Rotate(o, d^1);
                else Rotate(o->ch[d], d);
            }
            Rotate(o, d^1);
        }
    }
    Node* Build(int L, int R)
    {
        if (L > R) return null;
        int mid = (L + R) >> 1;
        Node* o = newNode(mid);
        o->ch[0] = Build(L, mid - 1);
        o->ch[1] = Build(mid + 1, R);
        PushUp(o);
        return o;
    }
    void Update_dummy()
    {
        PushUp(root->ch[1]);
        PushUp(root);
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
    void getSeq(vector<int>& res, Node* o)
    {
        if (o == null) return;
        PushDown(o);
        getSeq(res, o->ch[0]);
        res.push_back(o->v);
        getSeq(res, o->ch[1]);
    }
public:
    void Init(int n)
    {
        cur = pool;
        null = newNode(0);
        null->ch[0] = null->ch[1] = null;
        null->s = 0;
        root = newNode(0);
        root->s = 0;
        root->ch[1] = newNode(0);
        root->ch[1]->s = 0;
        root->ch[1]->ch[0] = Build(1, n);
        Update_dummy();
    }
    void OutPut()
    {
        vector<int> res;
        getSeq(res, root);
        int n = (int) res.size() - 1;
        for(int i = 1; i < n; ++i) {
            printf("%d%c", res[i], (i == n-1)? '\n' : ' ');
        }
    }
    void Flip(int l, int r)
    {
        getRange(l, r+1)->Flip();
        Update_dummy();
    }
    void Cut(int a, int b, int c)
    {
        getRange(a, b+1);
        Node* tmp = root->ch[1]->ch[0];
        root->ch[1]->ch[0] = null;
        Update_dummy();
        getRange(c+1, c+1) = tmp;
        Update_dummy();
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n < 0 && m < 0)
            break;
        Solver.Init(n);
        while(m--) {
            char op[10];
            scanf("%s", op);
            if(op[0] == 'C') {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);
                Solver.Cut(a, b, c);
            } else if(op[0] == 'F') {
                int a, b;
                scanf("%d%d", &a, &b);
                Solver.Flip(a, b);
            }
            //Solver.OutPut();
        }
        Solver.OutPut();
    }
    return 0;
}

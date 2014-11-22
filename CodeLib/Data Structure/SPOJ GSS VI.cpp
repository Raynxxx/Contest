/*
** SPOJ Can you answer these queries VI
** Created by Rayn @@ 2014/09/03
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 200005;
const int INF = 1 << 28;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
}

int N, Q;
int arr[MAXN];

class SplayTree
{
private:
    struct Node
    {
        Node *ch[2];
        int val;
        int sz;
        int sum, lmax, rmax, smax;

        inline void setValue(const int& x) {
            val = sum = lmax = rmax = smax = x;
            sz = 1;
        }
        inline int cmp(int k) const {
            int d = k - ch[0]->sz;
            if(d == 1) return -1;
            return (d <= 0)? 0 : 1;
        }
        inline void PushUp() {
            sz = ch[0]->sz + ch[1]->sz + 1;
            sum = ch[0]->sum + ch[1]->sum + val;
            lmax = max(ch[0]->lmax, ch[0]->sum + val + max(ch[1]->lmax, 0));
            rmax = max(ch[1]->rmax, ch[1]->sum + val + max(ch[0]->rmax, 0));
            smax = max(ch[0]->smax, ch[1]->smax);
            smax = max(smax, val + max(ch[0]->rmax + ch[1]->lmax, 0));
            smax = max(smax, val + max(ch[0]->rmax, ch[1]->lmax));
        }
    };

    Node *null, *root;
    Node pool[MAXN], *cur;

    inline Node* newNode(int x)
    {
        cur->setValue(x);
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    inline void CreateNull()
    {
        null = newNode(-INF);
        null->sum = null->sz = 0;
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
        if(d == 1)
        {
            k -= o->ch[0]->sz + 1;
        }
        if(d != -1)
        {
            Node* p = o->ch[d];
            int d2 = p->cmp(k);
            int k2 = (d2 == 0)? k : k - p->ch[0]->sz - 1;
            if(d2 != -1)
            {
                Splay(p->ch[d2], k2);
                if(d == d2)
                {
                    Rotate(o, d^1);
                }
                else
                {
                    Rotate(o->ch[d], d);
                }
            }
            Rotate(o, d^1);
        }
    }
    Node* Build(int L, int R)
    {
        if(L > R) return null;
        int M = (L + R) >> 1;
        Node* o = newNode(arr[M]);
        o->ch[0] = Build(L, M-1);
        o->ch[1] = Build(M+1, R);
        o->PushUp();
        return o;
    }
    inline void Update_dummy()
    {
        root->ch[1]->PushUp();
        root->PushUp();
    }
    inline Node* last() const
    {
        return root->ch[1]->ch[0];
    }
    inline Node*& getRange(int L, int R)
    {
        Splay(root, L);
        Splay(root->ch[1], R-L+1);
        return root->ch[1]->ch[0];
    }

public:
    void Init(int n)
    {
        cur = pool;
        CreateNull();
        root = newNode(-INF);
        root->sum = 0;
        root->ch[1] = newNode(INF);
        root->ch[1]->sum = 0;
        root->ch[1]->ch[0] = Build(1, n);
        Update_dummy();
    }
    void Insert(int pos, int x)
    {
        getRange(pos, pos) = newNode(x);
        Update_dummy();
    }
    void Delete(int pos)
    {
        getRange(pos, pos+1) = null;
        Update_dummy();
    }
    void Replace(int pos, int x)
    {
        getRange(pos, pos+1)->val = x;
        last()->PushUp();
    }
    int Query(int L, int R)
    {
        return getRange(L, R+1)->smax;
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char op[3];
    int x, y;
    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i)
        {
            readNumber(arr[i]);
        }
        Solver.Init(N);
        readNumber(Q);
        while(Q--)
        {
            scanf("%s", op);
            if(op[0] == 'I') {
                readNumber(x);
                readNumber(y);
                Solver.Insert(x++, y);
            } else if(op[0] == 'D') {
                readNumber(x);
                Solver.Delete(x++);
            } else if(op[0] == 'R') {
                readNumber(x);
                readNumber(y);
                Solver.Replace(x++, y);
            } else if(op[0] == 'Q') {
                readNumber(x);
                readNumber(y);
                printf("%d\n", Solver.Query(x++, y++));
            }
        }
    }
    return 0;
}

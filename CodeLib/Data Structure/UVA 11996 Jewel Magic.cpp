/*
** UVA 11996 Jewel Magic
** Created by Rayn @@ 2014/09/03
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef unsigned long long uLL;
const int MAXN = 400100;
const int INF = 0x3F3F3F3F;

uLL power[MAXN];
char pear[MAXN];

class SplayTree
{
private:
    struct Node
    {
        Node *ch[2];    //left & right son node
        int v;  //value of node
        int s;  //size of node
        int flip;  //flip or not
        uLL h1; //hash value
        uLL h2; //rev hash value

        inline int cmp(int k) const {
            int d = k - ch[0]->s;
            if(d == 1) return -1;
            return (d <= 0)? 0 : 1;
        }
        inline void Flip() {
            flip ^= 1;
            swap(ch[0], ch[1]);
            swap(h1, h2);
        }
        inline void PushUp() {
            s = ch[0]->s + ch[1]->s + 1;
            h1 = ch[0]->h1 * power[ch[1]->s+1] + v * power[ch[1]->s] + ch[1]->h1;
            h2 = ch[1]->h2 * power[ch[0]->s+1] + v * power[ch[0]->s] + ch[0]->h2;
        }
        inline void PushDown() {
            if(flip) {
                flip = 0;
                ch[0]->Flip();
                ch[1]->Flip();
            }
        }
    };

    Node pool[MAXN], *cur;
    Node *root, *null;
    char *str;

    inline Node* newNode(int val)
    {
        cur->flip = 0;
        cur->s = 1;
        cur->v = cur->h1 = cur->h2 = val;
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    inline void InitNull()
    {
        null = new Node();
        null->s = 0;
    }
    inline Node* Build(int L, int R)
    {
        int M = (L + R) >> 1;
        Node* o = newNode(str[M]);
        if(L < M)
            o->ch[0] = Build(L, M);
        if(M+1 < R)
            o->ch[1] = Build(M+1, R);
        o->PushUp();
        return o;
    }
    inline void Rotate(Node* &o, int d)
    {
        Node* k = o->ch[d^1];
        o->ch[d^1] = k->ch[d];
        k->ch[d] = o;
        o->PushUp();
        k->PushUp();
        o = k;
    }
    inline void Splay(Node* &o, int k)
    {
        o->PushDown();
        int d = o->cmp(k);
        if(d == 1) {
            k -= o->ch[0]->s + 1;
        }
        if(d != -1) {
            Node* p = o->ch[d];
            p->PushDown();
            int d2 = p->cmp(k);
            int k2 = (d2 == 0)? k : k - p->ch[0]->s - 1;
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
    inline void Update_dummy()
    {
        root->ch[1]->PushUp();
        root->PushUp();
    }
    Node* last() const
    {
        return root->ch[1]->ch[0];
    }
    Node*& getRange(int L, int R)
    {
        Splay(root, L);
        Splay(root->ch[1], R-L+1);
        return root->ch[1]->ch[0];
    }

public:
    void Init(char *s)
    {
        str = s;
        InitNull();

        cur = pool;
        root = newNode('[');
        root->ch[1] = newNode(']');
        root->ch[1]->ch[0] = Build(0, strlen(str));
        Update_dummy();
    }
    void Insert(int pos, int c)
    {
        getRange(pos+1, pos+1) = newNode(c + '0');
        Update_dummy();
    }
    void Remove(int pos)
    {
        getRange(pos, pos+1) = null;
        Update_dummy();
    }
    void Reverse(int L, int R)
    {
        getRange(L, R+1)->Flip();
        Update_dummy();
    }
    int getLCP(int x, int y)
    {
        int l = 0, r = root->s - y;
        while(l+1 < r)
        {
            int mid = (l + r) >> 1;
            uLL h1 = getRange(x, x+mid)->h1;
            uLL h2 = last()->h2;
            h1 -= getRange(y, y+mid)->h1;
            h2 -= last()->h2;
            if(!h1 && !h2) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    }
};

SplayTree ST;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N, M;
    power[0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        power[i] = power[i-1] * 7;
    }

    while(scanf("%d%d", &N, &M) != EOF)
    {
        scanf("%s", pear);
        ST.Init(pear);
        while(M--)
        {
            int op, x, y;
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d%d", &x, &y);
                ST.Insert(x, y);
            } else if(op == 2) {
                scanf("%d", &x);
                ST.Remove(x);
            } else if(op == 3) {
                scanf("%d%d", &x, &y);
                ST.Reverse(x, y);
            } else if(op == 4) {
                scanf("%d%d", &x, &y);
                printf("%d\n", ST.getLCP(x, y));
            }
        }
    }
    return 0;
}

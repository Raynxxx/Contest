/*
** HDU 4286 Data Handler
** Created by Rayn @@ 2014/09/02
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 1000010;
const int INF = 0x3F3F3F3F;

int N, M;
int arr[MAXN];

class SplayTree
{
private:
    struct Node
    {
        Node* ch[2];
        int v;
        int s;
        int flip;

        inline void setNode(int x) {
            flip = 0;
            s = 1;
            v = x;
        }
        inline int cmp(int k) const {
            int d = k - ch[0]->s;
            if(d == 1) return -1;
            return (d <= 0)? 0 : 1;
        }
        inline void PushUp() {
            s = ch[0]->s + ch[1]->s + 1;
        }
        inline void Flip() {
            flip ^= 1;
            swap(ch[0], ch[1]);
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

    inline Node* newNode(int x)
    {
        cur->setNode(x);
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    inline void CreateNull() {
        null = newNode(0);
        null->s = 0;
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
        o->PushDown();
        int d = o->cmp(k);
        if(d == 1) {
            k -= o->ch[0]->s + 1;
        }
        if(d != -1) {
            Node* p = o->ch[d];
            p->PushDown();
            int d2 = p->cmp(k);
            int k2 = (d2 == 0) ? k : k - p->ch[0]->s - 1;
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
    void Update_dummy()
    {
        root->ch[1]->PushUp();
        root->PushUp();
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
public:
    void Init(int N)
    {
        cur = pool;
        CreateNull();
        root = newNode(0);
        root->s = 0;
        root->ch[1] = newNode(0);
        root->ch[1]->s = 0;
        root->ch[1]->ch[0] = Build(1, N);
        Update_dummy();
    }
    void Insert(int pos, int x)
    {
        getRange(pos+1, pos+1) = newNode(x);
        Update_dummy();
    }
    void Delete(int pos)
    {
        getRange(pos, pos+1) = null;
        Update_dummy();
    }
    void Reverse(int L, int R)
    {
        getRange(L, R)->Flip();
        Update_dummy();
    }
    void printSeq(Node* o, vector<int>& res)
    {
        if(o == null) return ;
        o->PushDown();
        printSeq(o->ch[0], res);
        res.push_back(o->v);
        printSeq(o->ch[1], res);
    }
    void Print(int L, int R)
    {
        vector<int> res;
        printSeq(getRange(L, R+1), res);
        for(int i = 0; i < (int) res.size(); ++i) {
            printf("%d%c", res[i], (i == res.size() - 1)? '\n' : ' ');
        }
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &arr[i]);
        }
        Solver.Init(N);
        int L, R, tot = N;
        scanf("%d%d", &L, &R);
        scanf("%d", &M);
        while(M--)
        {
            char op[10], dir[10];
            scanf("%s", op);
            if(strcmp(op, "MoveLeft") == 0) {
                scanf("%s", dir);
                if(dir[0] == 'L'){
                    if(L > 1) L--;
                } else {
                    if(R > 1) R--;
                }
            } else if(strcmp(op, "MoveRight") == 0) {
                scanf("%s", dir);
                if(dir[0] == 'L'){
                    if(L < tot) L++;
                } else {
                    if(R < tot) R++;
                }
            } else if(strcmp(op, "Insert") == 0) {
                int x;
                scanf("%s%d", dir, &x);
                if(dir[0] == 'L') {
                    Solver.Insert(L-1, x);
                } else {
                    Solver.Insert(R, x);
                }
                R++; tot++;
            } else if(strcmp(op, "Delete") == 0) {
                scanf("%s", dir);
                if(dir[0] == 'L') {
                    Solver.Delete(L);
                } else {
                    Solver.Delete(R);
                }
                R--; tot--;
            } else if(strcmp(op, "Reverse") == 0) {
                Solver.Reverse(L, R+1);
            }
            //Solver.Print(1, tot);
        }
        Solver.Print(1, tot);
    }
    return 0;
}

/*
** UVA 11922 Permutation Transformer
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
typedef long long LL;
const int MAXN = 100000 + 10;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

class SplayTree
{
private:
    struct Node
    {
        Node* ch[2];
        int s;
        int flip;
        int v;
        int cmp(int k) const {
            int d = k - ch[0]->s;
            if(d == 1) return -1;
            return d <= 0 ? 0 : 1;
        }
        inline void PushUp() {
            s = ch[0]->s + ch[1]->s + 1;
        }
        inline void PushDown() {
            if(flip) {
                flip = 0;
                swap(ch[0], ch[1]);
                ch[0]->flip = !ch[0]->flip;
                ch[1]->flip = !ch[1]->flip;
            }
        }
    };

    int n;
    Node* root;
    Node* null;
    Node seq[MAXN];

    Node* Build(int sz)
    {
        if(!sz) return null;
        Node* L = Build(sz/2);
        Node* o = &seq[++n];
        o->v = n;
        o->ch[0] = L;
        o->ch[1] = Build(sz - sz/2 - 1);
        o->flip = o->s = 0;
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
    Node* Merge(Node* left, Node* right)
    {
        Splay(left, left->s);
        left->ch[1] = right;
        left->PushUp();
        return left;
    }
    Node* Split(Node* o, int k, Node* &left, Node* &right)
    {
        Splay(o, k);
        left = o;
        right = o->ch[1];
        o->ch[1] = null;
        left->PushUp();
    }
    void getAns(Node* o, vector<int>& ans)
    {
        if(o != null) {
            o->PushDown();
            getAns(o->ch[0], ans);
            ans.push_back(o->v-1);
            getAns(o->ch[1], ans);
        }
    }

public:
    void Init(int sz)
    {
        n = 0;
        null = new Node();
        root = Build(sz);
    }
    void Gao(int a, int b)
    {
        Node *left, *mid, *right;
        Split(root, a, left, right);
        //如果没有虚拟结点，a将改成a-1，违反split的限制
        Split(right, b-a+1, mid, right);
        mid->flip ^= 1;
        root = Merge(Merge(left, right), mid);
    }
    void printAns()
    {
        vector<int> ans;
        getAns(root, ans);
        for(int i = 1; (int) i < ans.size(); ++i) {
            printf("%d\n", ans[i]);
        }
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N, M;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        Solver.Init(N+1);
        //最前面有一个虚拟结点
        while(M--)
        {
            int a, b;
            //scanf("%d%d", &a, &b);
            readNumber(a);
            readNumber(b);
            Solver.Gao(a, b);
        }
        Solver.printAns();
    }
    return 0;
}

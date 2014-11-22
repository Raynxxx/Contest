/*
** POJ 3580 SuperMemo
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

const int MAXN = 200100;
const int INF = 1 << 27;

int N, M;
int arr[MAXN];

class SplayTree
{
private:
    struct Node
    {
        Node *ch[2];
        int s;
        int v;
        int flip;
        int minv;
        int add;

        inline int cmp(int k) const
        {
            int d = k - ch[0]->s;
            if (d == 1) return -1;
            return (d <= 0) ? 0 : 1;
        }
        inline void Add(int val)
        {
            v += val;
            add += val;
            minv += val;
        }
    };

    Node *cur, pool[MAXN];
    Node *root, *null;

    inline void PushUp(Node* o)
    {
        o->s = o->ch[0]->s + o->ch[1]->s + 1;
        o->minv = min(o->v, min(o->ch[0]->minv, o->ch[1]->minv));
    }
    inline void PushDown(Node* o)
    {
        if(o->flip) {
            o->flip = 0;
            swap(o->ch[0], o->ch[1]);
            o->ch[0]->flip ^= 1;
            o->ch[1]->flip ^= 1;
        }
        if(o->add) {
            if(o->ch[0] != null) o->ch[0]->Add(o->add);
            if(o->ch[1] != null) o->ch[1]->Add(o->add);
            o->add = 0;
        }
    }
    Node* newNode(int v)
    {
        cur->s = 1;
        cur->flip = cur->add = 0;
        cur->v = cur->minv = v;
        cur->ch[0] = cur->ch[1] = null;
        return cur++;
    }
    Node* Build(int L, int R)
    {
        if (L > R) return null;
        int mid = (L + R) >> 1;
        Node* o = newNode(arr[mid]);
        o->ch[0] = Build(L, mid - 1);
        o->ch[1] = Build(mid + 1, R);
        PushUp(o);
        return o;
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
        if (d == 1)
        {
            k -= o->ch[0]->s + 1;
        }
        if (d != -1)
        {
            Node* p = o->ch[d];
            PushDown(p);
            int d2 = p->cmp(k);
            int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
            if (d2 != -1)
            {
                Splay(p->ch[d2], k2);
                if (d == d2)
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
public:
    void Init(int n)
    {
        cur = pool;
        null = newNode(INF);
        null->ch[0] = null->ch[1] = null;
        null->s = 0;
        root = newNode(INF);
        root->s = 0;
        root->ch[1] = newNode(INF);
        root->ch[1]->s = 0;
        root->ch[1]->ch[0] = Build(1, n);
        Update_dummy();
    }
    void Add(int l, int r, int d)
    {
        getRange(l, r+1)->Add(d);
        Update_dummy();
    }
    void Reverse(int l, int r)
    {
        getRange(l, r+1)->flip ^= 1;
        Update_dummy();
    }
    void Revolve(int l, int r, int t)
    {
        int len = r - l + 1;
        t = (t % len + len) % len;
        if (t == 0) return;
        getRange(r-t+1, r+1);
        Node* tmp = root->ch[1]->ch[0];
        root->ch[1]->ch[0] = null;
        Update_dummy();
        getRange(l, l) = tmp;
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
    int getMin(int l, int r)
    {
        int ret = getRange(l, r+1)->minv;
        return ret;
    }
    void dfs(vector<int>& res, Node* o)
    {
        if (o == null) return;
        dfs(res, o->ch[0]);
        res.push_back(o->v);
        dfs(res, o->ch[1]);
    }
    void Debug()
    {
        vector<int> res;
        dfs(res, root);
        for (int i = 1; i < (int)res.size() - 1; ++i) {
            printf("%d ", res[i]);
        }
        puts("");
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i)
    {
        scanf("%d", &arr[i]);
    }
    Solver.Init(N);
    scanf("%d", &M);
    while (M--)
    {
        char op[10];
        scanf("%s", op);
        if (strcmp(op, "ADD") == 0) {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);
            Solver.Add(l, r, d);
        } else if (strcmp(op, "REVERSE") == 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            Solver.Reverse(l, r);
        } else if (strcmp(op, "REVOLVE") == 0) {
            int l, r, t;
            scanf("%d%d%d", &l, &r, &t);
            Solver.Revolve(l, r, t);
        } else if (strcmp(op, "INSERT") == 0) {
            int pos, x;
            scanf("%d%d", &pos, &x);
            Solver.Insert(pos, x);
        } else if (strcmp(op, "DELETE") == 0) {
            int pos;
            scanf("%d", &pos);
            Solver.Delete(pos);
        } else if (strcmp(op, "MIN") == 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", Solver.getMin(l, r));
        }
        //Solver.Debug();
    }
    return 0;
}

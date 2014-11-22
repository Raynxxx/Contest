/*
** HDU 3308 LCIS
** Created by Rayn @@ 2014/09/02
*/
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
const int MAXN = 100010;
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


int N, M;
int arr[MAXN];

struct SegmentTree
{
    struct Node
    {
        int left, right;
        int lval, rval;
        int lmax, rmax, smax;

        inline void makeNode(const int& val) {
            lval = rval = val;
            lmax = rmax = smax = 1;
        }
        inline int getMid() {
            return (left + right) >> 1;
        }
        inline int Length() {
            return (right - left + 1);
        }
    };

    Node tree[MAXN<<2];

    inline void PushUp(int rt)
    {
        tree[rt].lval = tree[lson].lval;
        tree[rt].rval = tree[rson].rval;

        tree[rt].lmax = tree[lson].lmax;
        if(tree[lson].lmax == tree[lson].Length() && tree[lson].rval < tree[rson].lval) {
            tree[rt].lmax += tree[rson].lmax;
        }
        tree[rt].rmax = tree[rson].rmax;
        if(tree[rson].rmax == tree[rson].Length() && tree[lson].rval < tree[rson].lval) {
            tree[rt].rmax += tree[lson].rmax;
        }

        tree[rt].smax = max(tree[lson].smax, tree[rson].smax);
        if(tree[lson].rval < tree[rson].lval) {
            tree[rt].smax = max(tree[rt].smax, tree[lson].rmax + tree[rson].lmax);
        }
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].left = l;
        tree[rt].right = r;
        if(l == r) {
            tree[rt].makeNode(arr[l]);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        PushUp(rt);
    }
    void Modify(int rt, int pos, int val)
    {
        if(tree[rt].left == tree[rt].right)
        {
            tree[rt].makeNode(val);
            return ;
        }
        int mid = tree[rt].getMid();
        if(pos <= mid) {
            Modify(lson, pos, val);
        } else {
            Modify(rson, pos, val);
        }
        PushUp(rt);
    }
    int Query(int rt, int x, int y)
    {
        if(x == tree[rt].left && tree[rt].right == y)
        {
            return tree[rt].smax;
        }
        int mid = tree[rt].getMid();
        if(y <= mid) {
            return Query(lson, x, y);
        } else if(mid < x) {
            return Query(rson, x, y);
        } else {
            int ret = 0, sub = 0;
            ret = max(Query(lson, x, mid), Query(rson, mid+1, y));
            if(tree[lson].rval < tree[rson].lval) {
                sub += min(tree[lson].rmax, mid-x+1);
                sub += min(tree[rson].lmax, y-mid);
            }
            return max(ret, sub);
        }
    }
};

SegmentTree Solver;
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, A, B;
    char op[4];

    scanf("%d", &T);
    while(T--)
    {
        readNumber(N);
        readNumber(M);
        for(int i = 1; i <= N; ++i)
        {
            readNumber(arr[i]);
        }
        Solver.Build(1, 1, N);
        while(M--)
        {
            scanf("%s", op);
            readNumber(A);
            readNumber(B);
            if(op[0] == 'U') {
                A++;
                Solver.Modify(1, A, B);
            } else if(op[0] == 'Q') {
                A++;
                B++;
                printf("%d\n", Solver.Query(1, A, B));
            }
        }
    }
    return 0;
}

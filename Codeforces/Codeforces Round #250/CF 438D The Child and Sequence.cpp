/*
** CF 438D The Child and Sequence
** Created by Rayn @@ 2014/10/01
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') {
        ch = getchar();
    }
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (T)(ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
}

const int MAXN = 100010;

class SegmentTree {
public:
    struct Node {
        int l, r;
        LL sum, maxv;
        inline int Length() {
            return r - l + 1;
        }
        inline int Mid() {
            return (l + r) >> 1;
        }
        inline void Set(const long long& v) {
            sum = maxv = v;
        }
    };

    Node tree[MAXN<<2];

    inline void PushUp(int rt) {
        tree[rt].sum = tree[lson].sum + tree[rson].sum;
        tree[rt].maxv = max(tree[lson].maxv, tree[rson].maxv);
    }
    void Build(int rt, int l, int r, long long value[])
    {
        tree[rt].l = l, tree[rt].r = r;
        if(l == r) {
            tree[rt].Set(value[l]);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid, value);
        Build(rson, mid+1, r, value);
        PushUp(rt);
    }
    LL PrintSum(int rt, int x, int y)
    {
        if(x <= tree[rt].l && tree[rt].r <= y) {
            return tree[rt].sum;
        }
        int mid = tree[rt].Mid();
        LL ret = 0;
        if(x <= mid)
            ret += PrintSum(lson, x, y);
        if(mid < y)
            ret += PrintSum(rson, x, y);
        return ret;
    }
    void Modulo(int rt, int x, int y, long long MOD)
    {
        if(tree[rt].maxv < MOD) return ;
        if(tree[rt].l == tree[rt].r) {
            tree[rt].sum %= MOD;
            tree[rt].maxv = tree[rt].sum;
            return ;
        }
        int mid = tree[rt].Mid();
        if(x <= mid)
            Modulo(lson, x, y, MOD);
        if(mid < y)
            Modulo(rson, x, y, MOD);
        PushUp(rt);
    }
    void Set(int rt, int pos, long long x)
    {
        if(tree[rt].l == pos && tree[rt].r == pos) {
            tree[rt].Set(x);
            return ;
        }
        int mid = tree[rt].Mid();
        if(pos <= mid)
            Set(lson, pos, x);
        else
            Set(rson, pos, x);
        PushUp(rt);
    }
};

SegmentTree ST;
long long a[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i) {
            readNumber(a[i]);
        }
        ST.Build(1, 1, n, a);
        while(m--) {
            int op, l, r, k;
            readNumber(op);
            if(op == 1) {
                readNumber(l);
                readNumber(r);
                LL sum = ST.PrintSum(1, l, r);
                printf("%I64d\n", sum);
            } else if(op == 2) {
                long long MOD;
                readNumber(l);
                readNumber(r);
                readNumber(MOD);
                ST.Modulo(1, l, r, MOD);
            } else if(op == 3) {
                long long x;
                readNumber(k);
                readNumber(x);
                ST.Set(1, k, x);
            }
        }
    }
    return 0;
}

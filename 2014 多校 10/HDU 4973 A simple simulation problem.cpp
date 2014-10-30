/*
** HDU 4973 A simple simulation problem
** Created by Rayn @@ 2014/08/29
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50010;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

struct SegmentTree
{
    struct SegNode
    {
        int l, r;
        LL tag, sum, maxv;
        int getMid() {
            return (l + r) >> 1;
        }
    };

    SegNode tree[MAXN<<2];
    LL power[52];

    void getPow()
    {
        power[0] = 1LL;
        for(int i = 1; i <= 50; ++i) {
            power[i] = power[i-1] * 2LL;
        }
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].l = l, tree[rt].r = r;
        tree[rt].tag = 0;
        if(l == r) {
            tree[rt].sum = tree[rt].maxv = 1LL;
            tree[rt].tag = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid);
        Build(rt<<1|1, mid+1, r);
        PushUp(rt);
    }
    void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
        tree[rt].maxv = max(tree[rt<<1].maxv, tree[rt<<1|1].maxv);
    }
    void PushDown(int rt)
    {
        if(tree[rt].tag)
        {
            tree[rt<<1].tag += tree[rt].tag;
            tree[rt<<1|1].tag += tree[rt].tag;
            LL pow2 = power[tree[rt].tag];
            tree[rt<<1].sum *= pow2;
            tree[rt<<1|1].sum *= pow2;
            tree[rt<<1].maxv *= pow2;
            tree[rt<<1|1].maxv *= pow2;
            tree[rt].tag = 0LL;
        }
    }
    int Find(int rt, LL& lsum, LL& rsum)
    {
        if(tree[rt].l == tree[rt].r)
        {
            rsum = tree[rt].sum - lsum + 1;
            return tree[rt].l;
        }
        PushDown(rt);
        if(lsum <= tree[rt<<1].sum) {
            return Find(rt<<1, lsum, rsum);
        } else {
            lsum -= tree[rt<<1].sum;
            return Find(rt<<1|1, lsum, rsum);
        }
    }
    void Update(int rt, int pos, LL val)
    {
        if (tree[rt].l == tree[rt].r)
        {
            tree[rt].sum += val;
            tree[rt].maxv += val;
            return;
        }
        int mid = tree[rt].getMid();
        PushDown(rt);
        if(pos <= mid) {
            Update(rt<<1, pos, val);
        } else {
            Update(rt<<1|1, pos, val);
        }
        PushUp(rt);
    }
    void Modify(int rt, LL x, LL y)
    {
        if (x > y) return;
        if (x <= tree[rt].l && tree[rt].r <= y)
        {
            tree[rt].sum *= 2LL;
            tree[rt].maxv *= 2LL;
            tree[rt].tag++;
            return;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        if(x <= mid)
            Modify(rt<<1, x, y);
        if(mid < y)
            Modify(rt<<1|1, x, y);
        PushUp(rt);
    }
    LL Query(int rt, LL x, LL y)
    {
        if (x > y) return 0LL;
        if (x <= tree[rt].l && tree[rt].r <= y) {
            return tree[rt].maxv;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        LL ret = 0LL;
        if(x <= mid)
            ret = max(ret, Query(rt<<1, x, y));
        if(mid < y)
            ret = max(ret, Query(rt<<1|1, x, y));
        return ret;
    }
};

SegmentTree Solver;
int n, m;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Solver.getPow();

    int T, cases = 0;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        printf("Case #%d:\n", ++cases);
        Solver.Build(1, 1, n);
        while(m--)
        {
            char op[5]; LL a, b;
            scanf("%s", op);
            readNumber(a);
            readNumber(b);
            LL x = a, y = b, left = 0LL, right = 0LL;
            LL l = Solver.Find(1, x, left);
            LL r = Solver.Find(1, y, right);
            if(op[0] == 'D') {
                if(l == r) {
                    Solver.Update(1, l, b-a+1);
                } else {
                    Solver.Update(1, l, left);
                    Solver.Update(1, r, y);
                    Solver.Modify(1, l+1, r-1);
                }
            } else {
                if(l == r) {
                    printf("%I64d\n", b-a+1);
                } else {
                    LL res = max(left, y);
                    res = max(res, Solver.Query(1, l+1, r-1));
                    printf("%I64d\n", res);
                }
            }
        }
    }
    return 0;
}

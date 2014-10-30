/*
** HDU 4893 Wow! Such Sequence!
** Created by Rayn @@ 2014/08/19
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;

LL Fib[120];

void getFibonacci()
{
    Fib[0] = Fib[1] = 1;
    for(int i = 2; i <= 80; ++i)
    {
        Fib[i] = Fib[i-1] + Fib[i-2];
    }
}

struct Segment
{
    int left, right;
    long long sum;
    bool tag;
    Segment() {}
    Segment(int l, int r, LL sum, bool tag):
        left(l), right(r), sum(sum), tag(tag) {}
    int mid() {
        return (left + right) >> 1;
    }
};

struct SegmentTree
{
    Segment tree[MAXN<<2];

    void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
        tree[rt].tag = tree[rt<<1].tag & tree[rt<<1|1].tag;
    }
    void BuildTree(int rt, int l, int r)
    {
        tree[rt] = Segment(l, r, 0, false);
        if(l == r)
            return ;
        int mid = tree[rt].mid();
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
        PushUp(rt);
    }
    LL Find(LL x)
    {
        if(x <= 1)
            return 1;
        int id = lower_bound(Fib, Fib+80, x) - Fib;
        return (Fib[id]-x < x-Fib[id-1])? Fib[id] : Fib[id-1];
    }
    void Update(int rt, int k, int d)
    {
        if(tree[rt].left == tree[rt].right)
        {
            tree[rt].tag = false;
            tree[rt].sum += d;
            return ;
        }
        int mid = tree[rt].mid();
        if(k <= mid)
            Update(rt<<1, k, d);
        else
            Update(rt<<1|1, k, d);
        PushUp(rt);
    }
    void Change(int rt, int l, int r)
    {
        if(tree[rt].tag)
            return ;
        if(tree[rt].left == tree[rt].right)
        {
            tree[rt].tag = true;
            tree[rt].sum = Find(tree[rt].sum);
            return ;
        }
        int mid = tree[rt].mid();
        if(l <= mid)
            Change(rt<<1, l, r);
        if(mid < r)
            Change(rt<<1|1, l, r);
        PushUp(rt);
    }
    LL Query(int rt, int l, int r)
    {
        if(l <= tree[rt].left && tree[rt].right <= r)
        {
            return tree[rt].sum;
        }
        LL ret = 0;
        int mid = tree[rt].mid();
        if(l <= mid)
            ret += Query(rt<<1, l, r);
        if(mid < r)
            ret += Query(rt<<1|1, l, r);
        return ret;
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    getFibonacci();
    int n, m, op;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Solver.BuildTree(1, 1, n);
        while(m--)
        {
            scanf("%d", &op);
            if(op == 1) {   //"add d to k-th"
                int k, d;
                scanf("%d%d", &k, &d);
                Solver.Update(1, k, d);
            } else if(op == 2) {    //"query sum"
                int l, r;
                scanf("%d%d", &l, &r);
                printf("%I64d\n", Solver.Query(1, l, r));
            } else if(op == 3) {    //"change to nearest Fibonacci"
                int l, r;
                scanf("%d%d", &l, &r);
                Solver.Change(1, l, r);
            }
        }
    }
    return 0;
}
